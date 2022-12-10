#ifndef MINES_CONTROL_H
#define MINES_CONTROL_H

#include <list>
#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "Sprite.h"
#include "Window.h"
#include "Collision.h"
#include "GameConfigs.h"
#include "Mine.h"

__BEGIN_API

class MinesControl
{
public:
    MinesControl();
    ~MinesControl();
    void setWindowReference(Window *window);
    void setCollisionReference(Collision *collision);
    void removeMine(Mine *enemy);

    void run();

private:
    void loadSprites();
    void createMine();
    void processLoop();
    void handleMines();

    // Referências de Window e Collision para passar para as Ships
    Window *_window;
    Collision *_collision;

    int DELAY_MINE_SPAWN;
	int DELAY_MINE_EXPLOSION;

    // Sprites
    std::list<Mine *> mines;
    std::shared_ptr<Timer> minesSpawnTimer;
    std::shared_ptr<Sprite> mineSprite;
    std::shared_ptr<Sprite> mineExplosionSprite;
	ALLEGRO_COLOR _color;
};

__END_API

#endif