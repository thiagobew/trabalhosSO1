#include "include/KeyBoard.h"

__BEGIN_API

Keyboard::Keyboard()
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

void Keyboard::run()
{
    while (!GameConfigs::finished)
    {
        db<Keyboard>(TRC) << ">>>> KEYBOARD starting loop\n";
        this->handleIO();
        Thread::yield();
    }
}

void Keyboard::handleIO()
{
    // Get the input
    al_get_keyboard_state(&this->kBoard);
    // Identifica e atualiza a action atual
    this->updateCurrentAction();
}

void Keyboard::updateCurrentAction()
{
    if (al_key_down(&this->kBoard, ALLEGRO_KEY_UP))
    {
        this->currentAction = GameAction::MOVE_UP;
    }
    else if (al_key_down(&this->kBoard, ALLEGRO_KEY_RIGHT))
    {
        this->currentAction = GameAction::MOVE_RIGHT;
    }
    else if (al_key_down(&this->kBoard, ALLEGRO_KEY_DOWN))
    {
        this->currentAction = GameAction::MOVE_DOWN;
    }
    else if (al_key_down(&this->kBoard, ALLEGRO_KEY_LEFT))
    {
        this->currentAction = GameAction::MOVE_LEFT;
    }
    else if (al_key_down(&this->kBoard, ALLEGRO_KEY_1))
    {
        std::cout << "missel\n";
        this->currentAction = GameAction::FIRE_PRIMARY;
    }
    else if (al_key_down(&this->kBoard, ALLEGRO_KEY_SPACE))
    {
        std::cout << "tiro normal\n";
        this->currentAction = GameAction::FIRE_SECONDARY;
    }
    else if (al_key_down(&this->kBoard, ALLEGRO_KEY_ESCAPE))
    {
        this->currentAction = GameAction::QUIT_GAME;
        std::cout << "sair\n";
    }
    else
    {
        this->currentAction = GameAction::NO_ACTION;
    }
}

__END_API