#include "include/Window.h"

__BEGIN_API

Window::Window()
{
    this->init();
}

Window::Window(int width, int height, int fps) : _displayWidth(width), _displayHeight(height), _fps(fps)
{
    this->init();
}

Window::~Window()
{
    if (this->_timer != NULL)
        al_destroy_timer(this->_timer);
    if (this->_eventQueue != NULL)
        al_destroy_event_queue(this->_eventQueue);
    if (this->_display != NULL)
        al_destroy_display(this->_display);

    bgSprite.reset();
    engineSprite.reset();
}

void Window::run()
{
    while (!Configs::finished)
    {
        this->handleEventQueue();
        this->draw();
        Thread::yield();
    }
}

void Window::handleEventQueue()
{
    ALLEGRO_EVENT event;
    float currentTime;

    // Get event
    al_wait_for_event(this->_eventQueue, &event);

    // Close display
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        std::cout << "Program should end\n";
        return;
    }

    // Timer
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        currentTime = al_current_time();
        this->update(currentTime - this->previousTime);
        this->previousTime = currentTime;
        this->redraw = true;
    }
}

void Window::draw()
{
    // Checa se é para desenhar e se a eventQueue está vazia
    if (this->redraw && al_is_event_queue_empty(this->_eventQueue))
    {
        this->redraw = false;
        this->drawBackground();
        al_flip_display();
    }
}

void Window::drawBackground()
{
    bgSprite->draw_parallax_background(bgMid.x, 0);
}

// initialize Allegro, the _display window, the addons, the timers, and event sources
void Window::init()
{
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

// Update the game time
void Window::update(double dt)
{
    this->bgMid = this->bgMid + this->bgSpeed * dt;
    if (bgMid.x >= 800)
    {
        bgMid.x = 0;
    }
}

void Window::loadSprites()
{
    // Create Ship
    shipPosition = Point(215, 245);
    color = al_map_rgb(0, 200, 0);

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
    engineSprite = std::make_shared<Sprite>("Sprite2.png"); // espaçonave do usuário
    bgSprite = std::make_shared<Sprite>("BGstars.png");     // fundo da tela - background

    // delete path
    al_destroy_path(path);
}

__END_API