#ifndef SPACESHOOTER_H
#define SPACESHOOTER_H

#include <iostream>
#include "threads/cpu.h"
#include "threads/traits.h"
#include "threads/thread.h"
#include "threads/semaphore.h"

#include "Window.h"
#include "KeyBoard.h"
#include "PlayerShip.h"
#include "GameConfigs.h"

__BEGIN_API

class SpaceShooter
{
public:
    SpaceShooter() {}
    ~SpaceShooter() {}

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
        delete windowObj;
    }

    static void playerShipFunc()
    {
        playerShipObj = new PlayerShip(SpaceShooter::kBoardObj);
        // Nesse ponto, pela ordem de criação das threads, todos os objetos foram criados, então arrumamos as referências
        windowObj->setPlayerShip(playerShipObj);
        playerShipObj->setWindowReference(windowObj);

        playerShipObj->run();
        // delete playerShipObj;
    }

    static void collisionFunc()
    {
        playerShipObj = new PlayerShip(SpaceShooter::kBoardObj);
        // Nesse ponto, pela ordem de criação das threads, todos os objetos foram criados, então arrumamos as referências
        windowObj->setPlayerShip(playerShipObj);
        playerShipObj->setWindowReference(windowObj);

        playerShipObj->run();
        // delete playerShipObj;
    }

    static void keyBoardFunc()
    {
        kBoardObj = new Keyboard();
        kBoardObj->run();
        // delete kBoardObj;
    }

    static Thread *playerShipThread;
    static Thread *windowThread;
    static Thread *keyboardThread;
    static Thread *collisionThread;

    static PlayerShip *playerShipObj;
    static Window *windowObj;
    static Keyboard *kBoardObj;
};

__END_API

#endif
