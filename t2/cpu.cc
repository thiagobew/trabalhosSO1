#include "cpu.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

void CPU::Context::save() { getcontext(&_context); }

void CPU::Context::load() { setcontext(&_context); }

CPU::Context::~Context() {
    if (_stack)
        delete _stack;
}

int CPU::switch_context(Context *from, Context *to) {
    if (from && to) {
        swapcontext(&from->_context, &to->_context);
        return 0;
    }

    return -1;
}

__END_API
