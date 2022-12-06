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
    virtual bool inWindow() = 0;
    virtual Point getMidPoint() = 0;
    virtual Point getTopLeftPoint() = 0;
    virtual Point getTopRightPoint() = 0;
    virtual Point getBottomLeftPoint() = 0;
    virtual Point getBottomRightPoint() = 0;
};

__END_API

#endif