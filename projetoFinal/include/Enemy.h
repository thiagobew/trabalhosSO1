#ifndef ENEMY_H
#define ENEMY_H

#include "threads/traits.h"
#include "Drawable.h"
#include "Hittable.h"

__BEGIN_API

class Enemy : public Drawable, public Hittable
{
public:
    virtual void kill() = 0;
};

__END_API

#endif