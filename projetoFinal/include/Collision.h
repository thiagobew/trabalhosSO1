#ifndef COLLISION_H
#define COLLISION_H

#include <list>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Projectile.h"

__BEGIN_API

class Collision
{
public:
    Collision();
    ~Collision();
    void run();

private:
    std::list<Drawable *> drawableItens;

    // Methods
    void init();
    void verifyCollisions();
    bool verifyIfHit();

    // Game object
    PlayerShip *_playerShip;
    Keyboard *_keyBoard;
};

__END_API

#endif