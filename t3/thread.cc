#include "thread.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

// Fazendo a next_id começar com 0, essa variável também mostra quantas threads existem no momento
unsigned int Thread::_next_id = 0;

// https://stackoverflow.com/questions/9110487/undefined-reference-to-a-static-member
// Precisamos declarar as variáveis staticas no arquivo .cpp
Thread *Thread::_running;
Thread Thread::_main;
CPU::Context Thread::_main_context;
Thread Thread::_dispatcher;
Thread::Ready_Queue Thread::_ready;

int Thread::switch_context(Thread *prev, Thread *next) {
    Thread::_running = next;
    return CPU::switch_context(prev->context(), next->context());
};

// Este método irá então criar a Thread main, passando como parâmetro para o contexto o
// ponteiro da função main recebido como argumento
void Thread::init(void (*main)(void *)) {
    // Cria a main thread
    std::string name = "Main";
    Thread::_main = new Thread(main, (void *)&name);
    Thread::_running = &Thread::_main;
    Thread::_main_context = *Thread::_main.context();

    Thread::_dispatcher = new Thread(&Thread::dispatcher);

    Thread::_main.context()->load();
};

int Thread::getTimestamp() {
    return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

void Thread::dispatcher() {
    Thread::_ready.begin();
    while (Thread::_ready.size() > 1) {
        // Retira próxima thread a ser executada
        Thread *next = Thread::_ready.remove_head()->object();
        // Altera o estado do escalonador
        Thread::_dispatcher._state = Thread::READY;

        // insert insere ordenado (importante para manter prioridade)
        Thread::_ready.insert(&Thread::_dispatcher._link);
        Thread::_running = next;
        next->_state = Thread::RUNNING;
        Thread::switch_context(&Thread::_dispatcher, next);

        if (Thread::_ready.head()->object()->_state == Thread::FINISHING) {
            Thread::_ready.remove_head();
        }
    }

    Thread::_dispatcher._state = Thread::FINISHING;
    Thread::_ready.remove(&Thread::_dispatcher);
    Thread::switch_context(&Thread::_dispatcher, &Thread::_main);
}

void Thread::yield() {
    Thread *next = Thread::_ready.remove_head()->object();
    Thread *prev = Thread::_running;
    if (Thread::_running != &Thread::_main || Thread::_running->_state == Thread::FINISHING)
        Thread::_running->_link.rank(Thread::getTimestamp());

    if (Thread::_running->_state != Thread::FINISHING) {
        Thread::_running->_state = Thread::READY;
        Thread::_ready.insert(&Thread::_running->_link);
    }

    Thread::_running = next;
    next->_state = Thread::RUNNING;
    Thread::switch_context(prev, next);
}

void Thread::thread_exit(int exit_code) {
    if (this->_context)
        delete this->_context;

    // Decrementa o next_id para saber quantas Threads ativas existem no SO
    Thread::_next_id -= 1;
};

__END_API
