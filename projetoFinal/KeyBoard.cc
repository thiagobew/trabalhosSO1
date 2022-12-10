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

Keyboard::~Keyboard()
{
    if (this->_eventQueue != NULL)
        al_destroy_event_queue(this->_eventQueue);
}

void Keyboard::run()
{
    while (!GameConfigs::finished)
    {
        db<Keyboard>(TRC) << ">>>> KEYBOARD starting loop\n";
        this->updateKeyboardStatus();
        Thread::yield();
    }
}

bool Keyboard::getKbKeyIsPressed(KbKey key)
{
    if (key == KbKey::MOVE_UP)
        return al_key_down(&this->kBoard, ALLEGRO_KEY_UP);
    else if (key == KbKey::MOVE_DOWN)
        return al_key_down(&this->kBoard, ALLEGRO_KEY_DOWN);
    else if (key == KbKey::MOVE_LEFT)
        return al_key_down(&this->kBoard, ALLEGRO_KEY_LEFT);
    else if (key == KbKey::MOVE_RIGHT)
        return al_key_down(&this->kBoard, ALLEGRO_KEY_RIGHT);
    else if (key == KbKey::ESC)
        return al_key_down(&this->kBoard, ALLEGRO_KEY_ESCAPE);
    else if (key == KbKey::NUM_1)
        return al_key_down(&this->kBoard, ALLEGRO_KEY_1);
    else if (key == KbKey::SPACE)
        return al_key_down(&this->kBoard, ALLEGRO_KEY_SPACE);
    else
        std::cout << "Cannot map this key;\n";
    return false;
}

void Keyboard::updateKeyboardStatus()
{
    // update the state of the keyboard variable
    al_get_keyboard_state(&this->kBoard);
}

__END_API