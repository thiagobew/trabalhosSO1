#ifndef BOSS_CONTROL_H
#define BOSS_CONTROL_H

#include <list>
#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Enemy.h"
#include "GameConfigs.h"
#include "Boss.h"
#include "Timer.h"
#include "Window.h"
#include "Collision.h"

__BEGIN_API

class BossControl
{
public:
    BossControl();
    ~BossControl();

    void setWindowReference(Window *window);
    void setCollisionReference(Collision *collision);

    void run();

private:
    void loadSprites();
    void createBoss();
    static int DELAY_UNTIL_BOSS;

    Boss *boss;
    // Referências de Window e Collision para passar para o boss
    Window *_window;
    Collision *_collision;

    // Sprites
    std::shared_ptr<Timer> bossSpawnTimer;
    std::shared_ptr<Sprite> bossSprite;
};

__END_API

#endif