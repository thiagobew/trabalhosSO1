#include "./traits.h"
#include <iostream>
#include <ucontext.h>

#ifndef GAMECONFIGS_H
#define GAMECONFIGS_H

__BEGIN_API

class GameConfigs
{
public:
    static int windowWidth;
    static int windowHeight;
    static int fps;
    static bool finished;
};

__END_API

#endif
