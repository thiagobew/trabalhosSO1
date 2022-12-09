#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "threads/traits.h"
#include "GameConfigs.h"
#include "Drawable.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Projectile : public Drawable
{
public:
	Projectile(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : _point(point), _color(color), _speed(speed),
																					isPlayerShot(isPlayerShot) {}
	virtual ~Projectile() {}

	virtual void draw() = 0;
	virtual void update(double diffTime) = 0;
	virtual int getSize() = 0;

	Point getPosition() { return this->_point; }
	bool getIsPlayerProjectile() { return this->isPlayerShot; }
	bool isOutside()
	{
		if ((this->_point.x > GameConfigs::windowWidth) ||
			(this->_point.x < 0) ||
			(this->_point.y > GameConfigs::windowHeight) ||
			(this->_point.y < 0))
			return true;
		return false;
	}

protected:
	Point _point;
	ALLEGRO_COLOR _color;
	Vector _speed;
	bool isPlayerShot;
};

__END_API

#endif