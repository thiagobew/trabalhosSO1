#include "include/Boss.h"

__BEGIN_API

int Boss::BOSS_LIFE = 50;
int Boss::BOSS_FIRE_SPEED = 50;

Boss::Boss(Point point, Vector vector, std::shared_ptr<Sprite> bossSprites) : Enemy(point, vector, Boss::BOSS_LIFE)
{
    this->bossSprites = bossSprites;
    this->color = al_map_rgb(0, 0, 0);

    this->shotsTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->shotsTimer->create();
    this->shotsTimer->startTimer();

    this->row = 0;
    this->col = 0;
    this->spritesIndex = 0;
    this->size = 80;
    this->invincible = true;
}

Boss::~Boss()
{
    this->shotsTimer.reset();
    this->bossSprites.reset();
    GameConfigs::bossExists = false;
}

void Boss::hit(int damage)
{
    if (!this->invincible)
        this->life -= damage;
}

void Boss::draw()
{
    this->updateSprite();
    if (!this->isDead())
        this->bossSprites->draw_boss(this->row, this->col, 200, 200, this->_point, 0);
}

void Boss::attack()
{
    this->_canFire = false;
}

bool Boss::isOutside() { return false; }

void Boss::update(double diffTime)
{
    this->_point = this->_point + this->_speed * diffTime;

    // Boss aparece e começa andando até chegar no ponto 650 da tela
    if (this->_point.x < 650 && this->invincible)
    {
        this->_speed.x = 0;
        this->_speed.y = -100;
        this->invincible = false;
    }

    // Quando o boss estiver indo pra baixo
    if (this->_point.y > (500 + rand() % 100) && this->_speed.y > 0)
        this->_speed.y = this->_speed.y * -1;

    // Quando o boss estiver indo pra cima
    if (this->_point.y < (150 + rand() % 100) && this->_speed.y < 0)
        this->_speed.y = this->_speed.y * -1;

    if (this->shotsTimer->getCount() > this->BOSS_FIRE_SPEED)
    {
        this->_canFire = true;
        this->shotsTimer->srsTimer();
    }
}

bool Boss::isDead() { return this->life <= 0; }

int Boss::getSize() { return this->size; }

void Boss::updateSprite()
{
    if (this->life > Boss::BOSS_LIFE)
        this->spritesIndex = 0;

    if (this->life <= Boss::BOSS_LIFE && this->spritesIndex < 3)
    {
        this->BOSS_FIRE_SPEED = rand() % 50 + 20;
        this->_speed = this->_speed * 1.1;
        this->size = 70;
        this->spritesIndex++;
    }
    // final damage animation-- fire speed up again
    if (this->life <= 20 && this->spritesIndex < 8)
    {
        this->BOSS_FIRE_SPEED = rand() % 30 + 20;
        this->_speed = this->_speed * 1.1;
        this->size = 60;
        this->spritesIndex++;
    }
    // interpret index as row and col of sprite sheet
    this->row = this->spritesIndex / 3;
    this->col = this->spritesIndex % 3;
}

__END_API