#ifndef MINE_H
#define MINE_H

#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "GameConfigs.h"
#include "MinesControl.h"

__BEGIN_API
class MinesControl; // Forward declaration, avoid compilation error

class Mine : public Enemy
{
public:
    Mine(Point point, Vector vector, std::shared_ptr<Sprite> mineSprite, std::shared_ptr<Sprite> deathSprite, MinesControl *control);
    ~Mine();

    bool canFire() { return false; }
    void draw();
    void attack();
    void update(double diffTime);
    bool isOutside();
    ALLEGRO_COLOR getColor() { return this->color; }
    int getSize();

private:
    // Logic
    std::shared_ptr<Timer> explodeTimer;

    // Controle do mine, é necessário essa referência para que quando o mine for destruído ele avisar para o control que foi destruido
    MinesControl *_control;

    // Sprites
    std::shared_ptr<Sprite> _mineSprite;
    std::shared_ptr<Sprite> _deathSprite;
    ALLEGRO_COLOR color;
    int deathSpriteTimer;
};

__END_API

#endif