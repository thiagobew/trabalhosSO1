#include "include/system.h"
#include "include/debug.h"
#include "include/thread.h"
#include "include/traits.h"
#include <iostream>

__BEGIN_API

void System::init(void (*main)(void *)) {
    db<System>(INF) << "System::init() chamado\n";
    setvbuf(stdout, 0, _IONBF, 0);

    Thread::init(main);
}

__END_API
