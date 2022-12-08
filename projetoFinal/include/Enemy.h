#ifndef ENEMY_H
#define ENEMY_H

#include "threads/traits.h"
#include "Drawable.h"
#include "Hittable.h"

__BEGIN_API

class Enemy : public Hittable
{
public:
    virtual void kill() = 0;
    // Hittable
    virtual void hit() = 0;
    virtual bool isDead() = 0;
    // Drawable
    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool isOutside() = 0;
    virtual int getSize() = 0;
    virtual Point getPosition() = 0;
};

__END_API

#endif