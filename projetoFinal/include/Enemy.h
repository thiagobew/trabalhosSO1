#ifndef ENEMY_H
#define ENEMY_H

#include "traits.h"

__BEGIN_API

class Enemy
{
public:
    virtual void kill() = 0;
};

__END_API

#endif