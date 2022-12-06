#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "threads/thread.h"
#include "threads/traits.h"

#include "GameConfigs.h"
#include "PlayerShip.h"
#include "Sprite.h"
#include "Vector.h"
#include "Action.h"

__BEGIN_API

class Keyboard
{

public:
    typedef act::KbKey KbKey;

    Keyboard();
    ~Keyboard();

    void init();
    void run();
    bool getKbKeyIsPressed(KbKey key);

private:
    // Methods
    void updateKeyboardStatus();

    // Time variables
    float startTime = 0;
    float currentTime = 0;

    // Allegro objects
    ALLEGRO_KEYBOARD_STATE kBoard;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
};

__END_API

#endif
