#ifndef window_h
#define window_h

#include "traits.h"
#include "thread.h"
#include "Sprite.h"
#include "Vector.h"
#include <stdio.h>

__BEGIN_API

#include <allegro5/allegro.h>
#include <memory>
#include <string>

// Classe para desenhar as coisas na tela
class Window
{
public:
    Window();
    Window(int width, int height, int fps);
    ~Window();

    void draw();
    void run();

private:
    // Methods
    void init();
    void loadSprites();
    void drawBackground();
    void handleEventQueue();
    void update(double diffTime);

    // Window variables
    int _displayWidth = 800;
    int _displayHeight = 600;
    int _fps = 60;
    bool redraw = true;

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