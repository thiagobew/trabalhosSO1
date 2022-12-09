#ifndef PURPLE_ENEMY_H
#define PURPLE_ENEMY_H

#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "GameConfigs.h"
#include "PurpleEnemiesControl.h"

__BEGIN_API

class PurpleEnemy : public Enemy
{
public:
    PurpleEnemy(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, std::shared_ptr<Sprite> deathSprite, PurpleEnemiesControl *control);
    ~PurpleEnemy();

    bool canFire() { return this->_canFire; }
    void draw();
    void attack();
    void update(double diffTime);
    bool isOutside();
    ALLEGRO_COLOR getColor() { return this->color; }
    int getSize();

private:
    // Logic
    bool _canFire;
    static int DELAY_BETWEEN_SHOTS;
    std::shared_ptr<Timer> shotsTimer;

    // Controle do ship, é necessário essa referência para que quando o ship for destruído ele avisar para o control que foi destruido
    PurpleEnemiesControl *_control;

    // Sprites
    std::shared_ptr<Sprite> _shipSprite;
    std::shared_ptr<Sprite> _deathSprite;
    ALLEGRO_COLOR color;
    int deathSpriteTimer;
};

__END_API

#endif