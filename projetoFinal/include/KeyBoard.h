#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "GameConfigs.h"
#include "PlayerShip.h"
#include "traits.h"
#include "Sprite.h"
#include "Vector.h"
#include "thread.h"
#include "Action.h"

__BEGIN_API

class Keyboard
{

public:
    typedef act::GameAction GameAction;

    Keyboard();
    ~Keyboard();

    void init();
    void run();
    GameAction getCurrentAction()
    {
        return this->currentAction;
    }

private:
    // Action variables
    GameAction currentAction;

    // Methods
    void handleIO();
    void updateCurrentAction();

    // Time variables
    float startTime = 0;
    float currentTime = 0;

    // Allegro objects
    ALLEGRO_KEYBOARD_STATE kBoard;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
};

__END_API

#endif
