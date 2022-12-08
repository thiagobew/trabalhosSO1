#ifndef window_h
#define window_h

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include <stdio.h>
#include <list> // Implementação de Lista ligada
#include "threads/thread.h"
#include "threads/traits.h"

#include "PlayerShip.h"
#include "KeyBoard.h"
#include "Sprite.h"
#include "Vector.h"
#include "Drawable.h"

__BEGIN_API

class Window
{
public:
    Window();
    Window(int width, int height, int fps);
    ~Window();
    void run();

    void setPlayerShip(PlayerShip *playerShip) { _playerShip = playerShip; }
    void setKeyboard(Keyboard *keyBoard) { _keyBoard = keyBoard; }
    void addDrawableItem(Drawable *item) { this->drawableItens.push_front(item); }
    void removeDrawableItem(Drawable *item) { this->drawableItens.remove(item); }

private:
    std::list<Drawable *> drawableItens;

    // Methods
    void init();
    void draw();
    void loadSprites();
    void drawBackground();
    void handleEventQueue();
    void updateBackGround(double diffTime);

    // Window variables
    int _displayWidth;
    int _displayHeight;
    int _fps;

    // Game object
    PlayerShip *_playerShip;
    Keyboard *_keyBoard;

    // Time variables
    float previousTime;

    // Background
    Point bgMid; /**<point used by the background to draw from */
    Point fgMid;
    Point fg2Mid;
    Vector bgSpeed; /**<background movement speed */
    Vector fgSpeed;
    std::shared_ptr<Sprite> bgSprite; /**<shared pointer to background animation */
    std::shared_ptr<Sprite> fgSprite;

    // Allegro objects
    ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    ALLEGRO_DISPLAY *_display;
};

__END_API

#endif