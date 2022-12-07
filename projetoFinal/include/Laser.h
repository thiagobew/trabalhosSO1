#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h>

#include "threads/traits.h"
#include "Point.h"
#include "Vector.h"
#include "Projectile.h"
#include "GameConfigs.h"

__BEGIN_API

class Laser : public Projectile
{
public:
    Laser(Point point, ALLEGRO_COLOR color, Vector vector, bool isPlayerShot);
    ~Laser();

    void draw();
    void update(double diffTime);
    int getSize();
};

__END_API

#endif