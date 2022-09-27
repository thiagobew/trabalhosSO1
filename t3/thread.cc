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
    return CPU::switch_context(prev->context(), next->context());
};

// Este método irá então criar a Thread main, passando como parâmetro para o contexto o
// ponteiro da função main recebido como argumento
// TODO: adicionar placement new para evitar memory leak
void Thread::init(void (*main)(void *)) {
    // Cria a main thread
    _main = *new Thread(main, (void *)"Main");
    _running = &_main;
	_main._state = RUNNING;
	// apenas para poder trocar para main
    _main_context = *new CPU::Context();

    _dispatcher = *new Thread(&dispatcher);

    CPU::switch_context(&_main_context, _main.context());
};

int Thread::getTimestamp() {
    return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

void Thread::dispatcher() {
    while (_ready.size() > 0) {
		db<Thread>(TRC) << "List size: " << _ready.size() << "\n";
        // Retira próxima thread a ser executada
        Thread *next = _ready.remove_head()->object();
        // Altera o estado do escalonador
        _dispatcher._state = READY;

        // insert insere ordenado (importante para manter prioridade)
        _ready.insert(&_dispatcher._link);
        _running = next;
        next->_state = RUNNING;
        switch_context(&_dispatcher, next);

        if (_ready.size() > 0 && _ready.head()->object()->_state == FINISHING) {
            _ready.remove_head();
        }
    }
	db<Thread>(TRC) << "Out of dispatcher while\n";
    _dispatcher._state = FINISHING;
    switch_context(&_dispatcher, &_main);
}

void Thread::yield() {
    Thread *next = _ready.remove_head()->object();
    Thread *prev = _running;
	db<Thread>(TRC) << "Running state: " << prev->_state << "\n";
    if (_running != &_main && _running->_state != FINISHING) {
        _running->_link.rank(getTimestamp());
        _running->_state = READY;
        _ready.insert(&_running->_link);
		db<Thread>(TRC) << "Thread " << _running->_id << " reinserted in list" << "\n";
    }

    _running = next;
    next->_state = RUNNING;
	db<Thread>(TRC) << "Switch " << prev->id() << " -> " << next->id() << "\n";
    switch_context(prev, next);
}

Thread::~Thread() {
	_ready.remove(&this->_link);
	if (this->_context)
        delete this->_context;
}

void Thread::thread_exit(int exit_code) {
    // Decrementa o next_id para saber quantas Threads ativas existem no SO
    _next_id -= 1;
	this->_state = FINISHING;
	yield();
};

__END_API
