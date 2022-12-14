#ifndef MISSILE_H
#define MISSILE_H

#include <allegro5/allegro.h>
#include <memory>
#include <vector>

#include "threads/traits.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Projectile.h"
#include "GameConfigs.h"

__BEGIN_API

class Missile : public Projectile
{
public:
    Missile(Point point, ALLEGRO_COLOR color, Vector vector, bool isPlayerShot);
    ~Missile();

    int getDamage();
    void ackHitSomething();
    bool wasDestroyed();

    void draw();
    void update(double diffTime);
    int getSize();

private:
    double angle;

    // Sprites
    void loadSprites();
    int currentSpriteIndex = 0;
    std::vector<std::shared_ptr<Sprite>> sprites;
    static int SPRITES_VECTOR_MAX_INDEX;
    static int DAMAGE;
};

__END_API

#endif