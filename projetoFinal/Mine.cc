#include "include/Mine.h"

__BEGIN_API

Mine::Mine(Point point, Vector vector, std::shared_ptr<Sprite> mineSprite, std::shared_ptr<Sprite> deathSprite, MinesControl *control) : Enemy(point, vector, 1)
{
    this->_mineSprite = mineSprite;
    this->_deathSprite = deathSprite;
    this->_control = control;
    this->deathSpriteTimer = 5;    
	this->color = al_map_rgb(150, 0, 150);
}

// Quando o inimigo morre ele manda uma mensagem para o controle falando que ele morreu, isso é necessário
// para removermos a referência ao objeto que vai ser destruído que está no controle
// É necessário pq não tem como o objeto Collision passar essa informação diretamente
Mine::~Mine()
{
    if (this->_control != nullptr)
        this->_control->removeMine(this);
}

void Mine::draw()
{
    if (this->isDead())
    {
        this->deathSpriteTimer -= 1;
        this->_deathSprite->draw_death_anim(this->deathSpriteTimer, this->_point, 0);
    }
    else
    {
        this->_mineSprite->draw_tinted(this->_point, this->color, 0);
    }
}

void Mine::update(double diffTime)
{
    this->_point = this->_point + this->_speed * diffTime;
}

int Mine::getSize() { return 24; }

bool Mine::isOutside() { return this->_point.x < -40; }

__END_API