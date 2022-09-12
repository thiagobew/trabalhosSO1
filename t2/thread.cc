#include "thread.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

int Thread::_next_id = 0;

int Thread::switch_context(Thread *prev, Thread *next) {
  _running = next;
  CPU::switch_context(prev->context(), next->context());
};

void Thread::thread_exit(int exit_code) { delete this; };

int Thread::id() { return _id; }

__END_API
