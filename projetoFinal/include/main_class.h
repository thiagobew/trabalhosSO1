#ifndef main_class_h
#define main_class_h

#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"
#include "Window.h"
#include "KeyBoard.h"
#include "PlayerShip.h"
#include "GameConfigs.h"
#include <iostream>

__BEGIN_API

class Main
{
public:
    Main() {}
    ~Main() {}

    // Essa função será passada para Thread::init()
    static void run(void *name)
    {
        windowThread = new Thread(windowFunc);
        keyboardThread = new Thread(keyBoardFunc);
        playerShipThread = new Thread(playerShipFunc);

        playerShipThread->join();
        windowThread->join();
        keyboardThread->join();

        delete playerShipThread;
        delete windowThread;
        delete keyboardThread;
    }

private:
    static void windowFunc()
    {
        windowObj = new Window(GameConfigs::windowWidth, GameConfigs::windowHeight, GameConfigs::fps);
        windowObj->run();
    }

    static void playerShipFunc()
    {
        playerShipObj = new PlayerShip(Main::kBoardObj);
        windowObj->setPlayerShip(playerShipObj);
        playerShipObj->run();
    }

    static void keyBoardFunc()
    {
        kBoardObj = new Keyboard();
        kBoardObj->run();
    }

    static Thread *playerShipThread;
    static Thread *windowThread;
    static Thread *keyboardThread;

    static PlayerShip *playerShipObj;
    static Window *windowObj;
    static Keyboard *kBoardObj;
};

__END_API

#endif
