#ifndef KBHANDLER_H
#define KBHANDLER_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "GameConfigs.h"
#include "Engine.h"
#include "traits.h"
#include "Sprite.h"
#include "Vector.h"
#include "thread.h"
#include "Action.h"

__BEGIN_API

class KeyboardHandler
{

public:
    KeyboardHandler();
    ~KeyboardHandler();

    void init();
    void run();

    void setPlayerShip(Engine *newPlayerShip)
    {
        this->playerShip = newPlayerShip;
    }

private:
    // Methods
    void handleIO();
    act::GameAction convertInputToAction();

    // Objects reference
    Engine *playerShip;

    // Time variables
    float startTime = 0;
    float currentTime = 0;

    // Allegro objects
    ALLEGRO_KEYBOARD_STATE kBoard;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
};

__END_API

#endif
