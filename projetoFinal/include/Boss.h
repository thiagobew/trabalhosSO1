#ifndef BOSS_H
#define BOSS_H

#include <list>
#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Enemy.h"
#include "Timer.h"
#include "Sprite.h"
#include "Window.h"
#include "Collision.h"
#include "Point.h"
#include "Vector.h"
#include "BossControl.h"

__BEGIN_API

class Boss : public Enemy
{
public:
    Boss(Point point, Vector vector, std::shared_ptr<Sprite> bossSprites, Window *window, Collision *collision);

    bool canFire() { return this->_canFire; }
    void draw();
    void attack();
    void update(double diffTime);
    void hit(int damage);
    bool isOutside();
    bool isDead();
    ALLEGRO_COLOR getColor() { return this->color; }
    int getSize();

private:
    static int BOSS_LIFE;

    // Logic
    bool _canFire;
    void updateSprite();
    int life;
    int fireSpeed;
    int size;
    bool invincible;

    // Referências de Window e Collision para passar para as Ships
    Window *_window;
    Collision *_collision;

    // Sprites
    int spritesIndex;
    std::shared_ptr<Timer> shotsTimer;
    std::shared_ptr<Sprite> bossSprites;
    ALLEGRO_COLOR color;
    int row;
    int col;
};

__END_API

#endif