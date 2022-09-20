#include "system.h"
#include "debug.h"
#include "traits.h"
#include <iostream>

__BEGIN_API

void System::init() {
    db<System>(INF) << "System::init() chamado\n";
    setvbuf(stdout, 0, _IONBF, 0);
}

__END_API
