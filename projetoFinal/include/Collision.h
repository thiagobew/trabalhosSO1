#ifndef COLLISION_H
#define COLLISION_H

#include <list>
#include "threads/thread.h"
#include "threads/traits.h"

#include "PlayerShip.h"
#include "Projectile.h"
#include "GameConfigs.h"
#include "Window.h"
#include "Enemy.h"

__BEGIN_API

class Collision
{
public:
    Collision();
    ~Collision();
    void setPlayerShip(PlayerShip *playerShip) { this->_playerShip = playerShip; }
    void setWindow(Window *window) { this->_window = window; }

    void addPlayerShot(Projectile *projectile) { this->playerShots.push_front(projectile); }
    void addEnemiesShot(Projectile *projectile) { this->enemiesShots.push_front(projectile); }
    void addEnemies(Enemy *enemy) { this->enemies.push_front(enemy); }
    void removeEnemy(Enemy *enemy) { this->enemies.remove(enemy); }
    void run();

private:
    // Game object
    std::list<Projectile *> enemiesShots;
    std::list<Projectile *> playerShots;
    std::list<Enemy *> enemies;
    PlayerShip *_playerShip;
    Window *_window;

    // Methods
    void verifyCollisions();
    bool verifyIfHit(Projectile *projectile, Hittable *hittable);
    bool verifyIfHit(Drawable *first, Drawable *second);

    void cleanOutsideObjects();
};

__END_API

#endif