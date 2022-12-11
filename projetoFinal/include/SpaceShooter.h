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

        std::cout << "Esperando PlayerShip\n";
        playerShipThread->join();
        std::cout << "Esperando windowThread\n";
        windowThread->join();
        std::cout << "Esperando keyboardThread\n";
        keyboardThread->join();
        std::cout << "Esperando collisionThread\n";
        collisionThread->join();
        std::cout << "Esperando purpleShipsControlThread\n";
        purpleShipsControlThread->join();
        std::cout << "Esperando minesControlThread\n";
        minesControlThread->join();
        std::cout << "Esperando bossSpawnThread\n";
        bossSpawnThread->join();

        std::cout << "Deletando PlayerShip\n";
        delete playerShipThread;
        std::cout << "Deletando Window\n";
        delete windowThread;
        std::cout << "Deletando KeyBoard\n";
        delete keyboardThread;
        std::cout << "Deletando Collision\n";
        delete collisionThread;
        std::cout << "Deletando Purple\n";
        delete purpleShipsControlThread;
        std::cout << "Deletando Mines\n";
        delete minesControlThread;
        std::cout << "Deletando Boss\n";
        delete bossSpawnThread;
        std::cout << "Terminou\n";
    }

private:
    static void windowFunc()
    {
        windowObj = new Window(GameConfigs::windowWidth, GameConfigs::windowHeight, GameConfigs::fps);
        windowObj->run();
        delete windowObj;
        windowThread->thread_exit(0);
    }

    static void playerShipFunc()
    {
        playerShipObj = new PlayerShip(SpaceShooter::kBoardObj);
        // Nesse ponto, pela ordem de criação das threads, todos os objetos foram criados, então arrumamos as referências
        windowObj->setPlayerShip(playerShipObj);
        playerShipObj->setWindowReference(windowObj);

        playerShipObj->run();
        delete playerShipObj;
        playerShipThread->thread_exit(0);
    }

    static void keyBoardFunc()
    {
        kBoardObj = new Keyboard();
        kBoardObj->run();
        delete kBoardObj;
        keyboardThread->thread_exit(0);
    }

    static void collisionFunc()
    {
        collisionObj = new Collision();
        collisionObj->setPlayerShip(playerShipObj);
        collisionObj->setWindow(windowObj);

        playerShipObj->setCollisionReference(collisionObj);

        collisionObj->run();
        delete collisionObj;
        collisionThread->thread_exit(0);
    }

    static void purpleShipsFunc()
    {
        purpleShipsControlObj = new PurpleEnemiesControl();
        purpleShipsControlObj->setCollisionReference(collisionObj);
        purpleShipsControlObj->setWindowReference(windowObj);
        purpleShipsControlObj->run();
        delete purpleShipsControlObj;
        purpleShipsControlThread->thread_exit(0);
    }

    static void minesFunc()
    {
        minesControlObj = new MinesControl();
        minesControlObj->setCollisionReference(collisionObj);
        minesControlObj->setWindowReference(windowObj);
        minesControlObj->run();
        delete minesControlObj;
        minesControlThread->thread_exit(0);
    }

    static void bossFunc()
    {
        bossControlObj = new BossControl();
        bossControlObj->setCollisionReference(collisionObj);
        bossControlObj->setWindowReference(windowObj);
        bossControlObj->setPlayerReference(playerShipObj);
        bossControlObj->run();
        delete bossControlObj;
        bossSpawnThread->thread_exit(0);
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
