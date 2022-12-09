#ifndef PURPLE_ENEMIES_CONTROL_H
#define PURPLE_ENEMIES_CONTROL_H

#include <list>
#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Sprite.h"
#include "Window.h"
#include "Collision.h"
#include "GameConfigs.h"
#include "PurpleEnemy.h"

__BEGIN_API

class PurpleEnemiesControl
{
public:
    PurpleEnemiesControl();
    ~PurpleEnemiesControl();
    void setWindowReference(Window *window);
    void setCollisionReference(Collision *collision);
    void removeShip(PurpleEnemy *enemy);

    void run();

private:
    void loadSprites();
    void createShips();
    void processLoop();
    void handleShips();
    int DELAY_SHIPS_SPAWN;

    // Referências de Window e Collision para passar para as Ships
    Window *_window;
    Collision *_collision;

    // Sprites
    std::list<PurpleEnemy *> ships;
    std::shared_ptr<Timer> shipsSpawnTimer;
    std::shared_ptr<Sprite> purpleShipSprite;
    std::shared_ptr<Sprite> enemyExplosionSprite;
};

__END_API

#endif