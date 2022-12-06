#include "include/threads/cpu.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

void CPU::Context::save() { getcontext(&_context); }

void CPU::Context::load() { setcontext(&_context); }

CPU::Context::~Context()
{
	if (_stack)
		delete _stack;
}

int CPU::switch_context(Context *from, Context *to)
{
	if (from && to)
		return swapcontext(&from->_context, &to->_context);
	return -1;
}

int CPU::finc(volatile int &number)
{
	register int old = 1;
	asm("lock xadd %0, %2"
		: "=a"(old)
		: "a"(old), "m"(number));
	return old;
}

int CPU::fdec(volatile int &number)
{
	register int old = -1;
	asm("lock xadd %0, %2"
		: "=a"(old)
		: "a"(old), "m"(number));
	return old;
}

__END_API
