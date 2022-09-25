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

void Thread::thread_exit(int exit_code) {
    if (this->_context)
        delete this->_context;

    // Decrementa o next_id para saber quantas Threads ativas existem no SO
    Thread::_next_id -= 1;
};

int Thread::id() { return _id; }

__END_API
