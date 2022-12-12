#ifndef ENEMY_H
#define ENEMY_H

#include "threads/traits.h"
#include "Drawable.h"
#include "Hittable.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Enemy : public Hittable
{
public:
    Enemy(Point point, Vector vector, int lifeQuant)
    {
        this->life = lifeQuant;
        this->_point = point;
        this->_speed = vector;
        this->_dead = false;
    }

    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool isOutside() = 0;
    virtual int getSize() = 0;
    virtual bool canFire() = 0;

    Point getPosition() { return this->_point; }
    Vector getVector() { return this->_speed; }
    void hit(int damage) { this->life -= damage; }
    bool isDead() { return _dead && this->life <= 0; }
    int getLife() { return this->life; }

protected:
    Point _point;
    Vector _speed;
    int life;
    bool _dead;

};

__END_API

#endif