#include "thread.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

unsigned int Thread::_next_id = 0;

// https://stackoverflow.com/questions/9110487/undefined-reference-to-a-static-member
// Precisamos declarar as variáveis staticas no arquivo .cpp
Thread *Thread::_running;
Thread *Thread::_mainThread;

int Thread::switch_context(Thread *prev, Thread *next) {
    // "Valor de retorno é negativo se houve erro, ou zero."
    if (!prev || !next || !prev->context() || !next->context())
        return -1;

    Thread::_running = next;
    CPU::switch_context(prev->context(), next->context());
    return 0;
};

void Thread::thread_exit(int exit_code) {
    if (this->_context)
        delete this->_context;

    if (Thread::_mainThread)
        switch_context(this, Thread::_mainThread);
};

int Thread::id() { return _id; }

__END_API
