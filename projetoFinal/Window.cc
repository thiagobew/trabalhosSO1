#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "include/Window.h"
#include "include/GameConfigs.h"

__BEGIN_API

Window::Window() { this->init(); }

Window::Window(int width, int height, int fps) : _displayWidth(width), _displayHeight(height), _fps(fps) { this->init(); }

Window::~Window()
{
    if (this->_timer != NULL)
        al_destroy_timer(this->_timer);
    if (this->_eventQueue != NULL)
        al_destroy_event_queue(this->_eventQueue);
    if (this->_display != NULL)
        al_destroy_display(this->_display);

    bgSprite.reset();
}

void Window::run()
{
    while (!GameConfigs::finished)
    {
        db<Window>(TRC) << ">>>> WINDOW starting loop\n";
        this->handleEventQueue();
        Thread::yield();
    }
}

void Window::handleEventQueue()
{
    ALLEGRO_EVENT event;

    // Get event
    al_wait_for_event(this->_eventQueue, &event);

    // Close display
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        GameConfigs::finished = true;
        return;
    }

    // Timer
    if (event.type == ALLEGRO_EVENT_TIMER)
        this->draw();
}

void Window::draw()
{
    // Checa se é para desenhar e se a eventQueue está vazia
    if (al_is_event_queue_empty(this->_eventQueue))
    {
        // Atualiza o timer
        float currentTime = al_current_time();
        double diffTime = currentTime - this->previousTime;
        this->previousTime = currentTime;

        // Update e draw
        this->updateBackGround(diffTime);
        this->drawBackground();

        if (this->_playerShip != nullptr)
        {
            this->_playerShip->update(diffTime);
            this->_playerShip->draw();
        }

        std::list<Drawable *> toRemove;
        // Para cada item para desenhar faz update, desenha e caso já tenha terminado então coloca numa outra lista para remover
        for (auto listItem = this->drawableItens.begin(); listItem != this->drawableItens.end(); listItem++)
        {
            Drawable *drawableItem = *listItem;
            drawableItem->update(diffTime);
            drawableItem->draw();
            if (!drawableItem->stillLive())
                toRemove.push_front(drawableItem);
        }

        // Para cada item que está nessa lista remove da lista original
        for (auto listItem = toRemove.begin(); listItem != toRemove.end(); listItem++)
        {
            Drawable *drawableItem = *listItem;
            this->drawableItens.remove(drawableItem);
            delete drawableItem;
        }

        al_flip_display();
    }
}

void Window::updateBackGround(double dt)
{
    this->bgMid = this->bgMid + this->bgSpeed * dt;
    if (bgMid.x >= 800)
        bgMid.x = 0;
}

void Window::drawBackground() { bgSprite->draw_parallax_background(bgMid.x, 0); }

void Window::init()
{
    db<Window>(TRC) << "Window Init started\n";
    // initialize allegro
    al_init();

    // create the display
    if ((this->_display = al_create_display(this->_displayWidth, this->_displayHeight)) == NULL)
    {
        std::cout << "Cannot initialize the display\n";
        exit(1);
    }

    // initialize addons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    // initialize our timers
    if ((this->_timer = al_create_timer(1.0 / this->_fps)) == NULL)
    {
        std::cout << "error, could not create timer\n";
        exit(1);
    }

    if ((this->_eventQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }

    // register our allegro _eventQueue
    al_register_event_source(this->_eventQueue, al_get_display_event_source(this->_display));
    al_register_event_source(this->_eventQueue, al_get_timer_event_source(this->_timer));
    al_start_timer(this->_timer);

    this->loadSprites();
}

void Window::loadSprites()
{
    // represents the middle of the image width-wise, and top height-wise
    bgMid = Point(0, 0);
    fgMid = Point(800, 0);
    fg2Mid = Point(300, 300);
    bgSpeed = Vector(50, 0);
    fgSpeed = Vector(-90, 0);

    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    // sprites
    bgSprite = std::make_shared<Sprite>("BGstars.png"); // fundo da tela - background

    // delete path
    al_destroy_path(path);
}

__END_API