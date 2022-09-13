#include "thread.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

int Thread::_next_id = 0;
Thread *Thread::_mainThread = 0;
Thread *Thread::_running = 0;

int Thread::switch_context(Thread *prev, Thread *next) {

  if (!prev->context() || !next->context()) {
    return -1;
  }

  _running = next;
  CPU::switch_context(prev->context(), next->context());
  return 0;
};

void Thread::thread_exit(int exit_code) {
  switch_context(this, _mainThread);
  this->~Thread();
};

int Thread::id() { return _id; }

__END_API
