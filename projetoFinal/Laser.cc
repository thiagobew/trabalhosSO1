#include <allegro5/allegro_primitives.h>
#include "include/Laser.h"

__BEGIN_API

Laser::Laser(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : Projectile(point, color, speed, isPlayerShot) {}

Laser::~Laser() {}

void Laser::draw()
{
    Point otherPoint = this->_point + this->_speed * (0.05);
    al_draw_line(this->_point.x, this->_point.y, otherPoint.x, otherPoint.y, this->_color, 3);
}

void Laser::update(double diffTime)
{
    this->_point = this->_point + this->_speed * diffTime;
}

int Laser::getSize() { return 3; }

__END_API