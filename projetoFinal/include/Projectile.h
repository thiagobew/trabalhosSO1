#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "traits.h"
#include "Drawable.h"

__BEGIN_API

class Projectile : public Drawable
{
public:
    virtual bool draw() = 0;
    virtual bool inWindow() = 0;
    virtual int getMidPoint() = 0;
    virtual int getTopLeftPoint() = 0;
    virtual int getTopRightPoint() = 0;
    virtual int getBottomLeftPoint() = 0;
    virtual int getBottomRightPoint() = 0;
};

__END_API

#endif