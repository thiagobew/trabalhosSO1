#include "include/PurpleEnemy.h"

__BEGIN_API

int PurpleEnemy::DELAY_BETWEEN_SHOTS = 50;

PurpleEnemy::PurpleEnemy(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, std::shared_ptr<Sprite> deathSprite, PurpleEnemiesControl *control) : Enemy(point, vector, 1)
{
    this->_shipSprite = shipSprite;
    this->_deathSprite = deathSprite;
    this->_control = control;
    this->deathSpriteTimer = 5;

    this->color = al_map_rgb(150, 0, 150);
    this->shotsTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->shotsTimer->create();
    this->shotsTimer->startTimer();
}

// Quando o inimigo morre ele manda uma mensagem para o controle falando que ele morreu, isso é necessário
// para removermos a referência ao objeto que vai ser destruído que está no controle
// É necessário pq não tem como o objeto Collision passar essa informação diretamente
PurpleEnemy::~PurpleEnemy()
{
    if (this->_control != nullptr && GameConfigs::finished == false)
        this->_control->removeShip(this);
}

void PurpleEnemy::draw()
{
    if (this->life <= 0)
    {
        this->deathSpriteTimer -= 1;
        this->_deathSprite->draw_death_anim(this->deathSpriteTimer, this->_point, 0);
        if (this->deathSpriteTimer <= 0)
            _dead = true;
    }
    else
    {
        this->_shipSprite->draw_tinted(this->_point, this->color, 0);
    }
}

void PurpleEnemy::update(double diffTime)
{
    if (_dead)
    {
        return;
    }

    this->_point = this->_point + this->_speed * diffTime;
    // Generate random number to have different delays between shots
    int moreDelay = rand() % 60;
    if (this->shotsTimer->getCount() > PurpleEnemy::DELAY_BETWEEN_SHOTS + moreDelay)
    {
        this->_canFire = true;
        this->shotsTimer->srsTimer();
    }
}

int PurpleEnemy::getSize() { return 20; }

bool PurpleEnemy::isOutside() { return this->_point.x < -40; }

void PurpleEnemy::attack() { this->_canFire = false; }

__END_API