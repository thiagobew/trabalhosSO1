#include "include/system.h"
#include "include/threads/debug.h"
#include "include/threads/thread.h"
#include "include/threads/traits.h"
#include <iostream>

__BEGIN_API

void System::init(void (*main)(void *))
{
	setvbuf(stdout, 0, _IONBF, 0);
	Thread::init(main);
}

__END_API
