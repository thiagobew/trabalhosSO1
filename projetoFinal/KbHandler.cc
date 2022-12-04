#include "include/KbHandler.h"

__BEGIN_API

KeyboardHandler::KeyboardHandler()
{
    if ((this->_eventQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }

    // install keyboard
    if (!al_install_keyboard())
    {
        std::cerr << "Could not install keyboard\n";
    }

    // register keyboard
    al_register_event_source(this->_eventQueue, al_get_keyboard_event_source());
}

void KeyboardHandler::run()
{
    while (!GameConfigs::finished)
    {
        this->handleIO();
        Thread::yield();
    }
}

void KeyboardHandler::handleIO()
{
    // Get the input
    al_get_keyboard_state(&this->kBoard);
    // Identifica e executa código necessário
    this->convertInputToAction();
}

act::GameAction KeyboardHandler::convertInputToAction()
{
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_UP))
    {
        return act::GameAction::MOVE_UP;
    }
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_RIGHT))
    {
        return act::GameAction::MOVE_RIGHT;
    }
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_DOWN))
    {
        return act::GameAction::MOVE_DOWN;
    }
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_LEFT))
    {
        return act::GameAction::MOVE_LEFT;
    }
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_1))
    {
        std::cout << "missel\n";
        return act::GameAction::FIRE_PRIMARY;
    }
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_SPACE))
    {
        std::cout << "tiro normal\n";
        return act::GameAction::FIRE_SECONDARY;
    }
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_ESCAPE))
    {
        std::cout << "sair\n";
        return act::GameAction::QUIT_GAME;
    }

    return act::GameAction::NO_ACTION;
}

__END_API