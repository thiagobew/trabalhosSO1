/**
 * @file GameConfig.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef GAMECONFIGS_H
#define GAMECONFIGS_H

#include "threads/traits.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

class GameConfigs
{
public:
    static int windowWidth;
    static int windowHeight;
    static int fps;
    static bool finished;
    static bool bossExists;
};

__END_API

#endif
