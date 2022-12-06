#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "threads/traits.h"
#include "Point.h"

__BEGIN_API

class Drawable
{
public:
    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool stillLive() = 0;
    virtual int getSize() = 0;
    virtual Point getPosition() = 0;
};

__END_API

#endif