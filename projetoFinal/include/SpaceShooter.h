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
#include "Collision.h"
#include "GameConfigs.h"
#include "PurpleEnemiesControl.h"
#include "MinesControl.h"
#include "BossControl.h"

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
        collisionThread = new Thread(collisionFunc);
        purpleShipsControlThread = new Thread(purpleShipsFunc);
        minesControlThread = new Thread(minesFunc);
        bossSpawnThread = new Thread(bossFunc);

        playerShipThread->join();
        windowThread->join();
        keyboardThread->join();
        collisionThread->join();
        purpleShipsControlThread->join();
        minesControlThread->join();
        bossSpawnThread->join();

        delete playerShipThread;
        delete windowThread;
        delete keyboardThread;
        delete collisionThread;
        delete purpleShipsControlThread;
        delete minesControlThread;
        delete bossSpawnThread;
    }

private:
    static void windowFunc()
    {
        windowObj = new Window(GameConfigs::windowWidth, GameConfigs::windowHeight, GameConfigs::fps);
        windowObj->run();
        std::cout << "BBB\n";
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

    static void keyBoardFunc()
    {
        kBoardObj = new Keyboard();
        kBoardObj->run();
        // delete kBoardObj;
    }

    static void collisionFunc()
    {
        collisionObj = new Collision();
        collisionObj->setPlayerShip(playerShipObj);
        collisionObj->setWindow(windowObj);
        playerShipObj->setCollisionReference(collisionObj);
        collisionObj->run();
    }

    static void purpleShipsFunc()
    {
        purpleShipsControlObj = new PurpleEnemiesControl();
        purpleShipsControlObj->setCollisionReference(collisionObj);
        purpleShipsControlObj->setWindowReference(windowObj);
        purpleShipsControlObj->run();
    }

    static void minesFunc()
    {
        minesControlObj = new MinesControl();
        minesControlObj->setCollisionReference(collisionObj);
        minesControlObj->setWindowReference(windowObj);
        minesControlObj->run();
    }

    static void bossFunc()
    {
        bossControlObj = new BossControl();
        bossControlObj->setCollisionReference(collisionObj);
        bossControlObj->setWindowReference(windowObj);
        bossControlObj->setPlayerReference(playerShipObj);
        bossControlObj->run();
    }

    static Thread *playerShipThread;
    static Thread *windowThread;
    static Thread *keyboardThread;
    static Thread *collisionThread;
    static Thread *purpleShipsControlThread;
    static Thread *minesControlThread;
    static Thread *bossSpawnThread;

    static PlayerShip *playerShipObj;
    static Window *windowObj;
    static Keyboard *kBoardObj;
    static Collision *collisionObj;
    static PurpleEnemiesControl *purpleShipsControlObj;
    static MinesControl *minesControlObj;
    static BossControl *bossControlObj;
};

__END_API

#endif
