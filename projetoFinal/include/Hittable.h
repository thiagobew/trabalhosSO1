#ifndef HITTABLE_H
#define HITTABLE_H

#include "threads/traits.h"

__BEGIN_API

class Hittable
{
public:
    virtual ~Hittable() {}

    virtual void hit() = 0;
    virtual bool isDead() = 0;
};

__END_API

#endif