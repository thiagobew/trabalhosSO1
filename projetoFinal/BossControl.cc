#include "include/BossControl.h"

__BEGIN_API

int BossControl::DELAY_UNTIL_BOSS = GameConfigs::fps * 60;

BossControl::BossControl()
{
    this->bossSpawnTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->bossSpawnTimer->create();
    this->bossSpawnTimer->startTimer();
}

void BossControl::setWindowReference(Window *window) { this->_window = window; }

void BossControl::setCollisionReference(Collision *collision) { this->_collision = collision; }

void BossControl::run()
{
    while (this->bossSpawnTimer->getCount() < BossControl::DELAY_UNTIL_BOSS)
    {
        Thread::yield();
    }

    this->loadSprites();
    this->createBoss();
    GameConfigs::bossHasAppeared = true;
}

void BossControl::createBoss()
{
    Boss *boss = new Boss(Point(GameConfigs::windowWidth, GameConfigs::windowHeight / 2),
                          Vector(-200, 0), this->bossSprite, this->_window, this->_collision);
    this->_window->addDrawableItem(boss);
    this->_collision->addEnemies(boss);
}

void BossControl::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    // sprites
    this->bossSprite = std::make_shared<Sprite>("bossv2.png");

    // delete path
    al_destroy_path(path);
}

__END_API