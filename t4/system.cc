#include "system.h"
#include "debug.h"
#include "thread.h"
#include "traits.h"
#include <iostream>

__BEGIN_API

void System::init(void (*main)(void *)) {
    db<System>(INF) << "System::init() chamado\n";
    setvbuf(stdout, 0, _IONBF, 0);

    Thread::init(main);
}

__END_API
