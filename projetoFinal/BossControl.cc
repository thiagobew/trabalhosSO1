#include "include/BossControl.h"

__BEGIN_API

int BossControl::DELAY_UNTIL_BOSS = GameConfigs::fps * 60;

BossControl::BossControl()
{
    this->bossSpawnTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->bossSpawnTimer->create();
    this->bossSpawnTimer->startTimer();

    this->bossWasSpawned = false;
}

BossControl::~BossControl()
{
    this->bossSpawnTimer.reset();
    this->bossSprite.reset();
}

void BossControl::setWindowReference(Window *window) { this->_window = window; }

void BossControl::setCollisionReference(Collision *collision) { this->_collision = collision; }

void BossControl::setPlayerReference(PlayerShip *player) { this->_playerShip = player; }

void BossControl::run()
{
    this->loadSprites();

    while (this->bossSpawnTimer->getCount() < BossControl::DELAY_UNTIL_BOSS && GameConfigs::finished == false)
        Thread::yield();

    if (GameConfigs::finished == false)
    {
        this->createBoss();
        this->bossWasSpawned = true;
        GameConfigs::bossExists = true;

        // Loop enquanto o boss estiver vivo
        while (!GameConfigs::finished && GameConfigs::bossExists)
        {
            if (this->boss->canFire())
            {
                this->boss->attack();
                Point playerPos = this->_playerShip->getPosition();

                Vector vectorAim(0, 0);
                // Mira no player um pouco acima do player
                vectorAim.Angle(playerPos, this->boss->getPosition() + Point(0, 30), 0.9);

                Missile *missile1 = new Missile(this->boss->getPosition(), this->boss->getColor(), vectorAim, false);

                // Mira no player um pouco abaixo do player
                vectorAim.Angle(playerPos, this->boss->getPosition() + Point(0, -30), 0.9);
                Missile *missile2 = new Missile(this->boss->getPosition(), this->boss->getColor(), vectorAim, false);

                this->_collision->addEnemiesShot(missile1);
                this->_collision->addEnemiesShot(missile2);

                this->_window->addDrawableItem(missile1);
                this->_window->addDrawableItem(missile2);
            }

            Thread::yield();
        }
    }
}

void BossControl::createBoss()
{
    this->boss = new Boss(Point(800, 300), Vector(-50, 0), this->bossSprite);
    this->_window->receiveBoss(boss);
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