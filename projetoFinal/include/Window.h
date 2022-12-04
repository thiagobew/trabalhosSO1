#ifndef window_h
#define window_h

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "PlayerShip.h"
#include "traits.h"
#include "thread.h"
#include "Sprite.h"
#include "Vector.h"
#include <stdio.h>

__BEGIN_API

// Classe para desenhar as coisas na tela
class Window
{
public:
    Window();
    Window(int width, int height, int fps);
    ~Window();

    // Função para atualizar a referência que Window precisa ter de PlayerShip
    // Por enquanto há uma necessidade de Window ser criada antes que PlayerShip para carregar as bibliotecas
    void setPlayerShip(PlayerShip *playerShip)
    {
        _playerShip = playerShip;
    }

    void run();

private:
    // Methods
    void init();
    void draw();
    void loadSprites();
    void drawBackground();
    void handleEventQueue();
    void update(double diffTime);

    // Window variables
    int _displayWidth;
    int _displayHeight;
    int _fps;
    bool mustRedraw;

    // Game object
    PlayerShip *_playerShip;

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