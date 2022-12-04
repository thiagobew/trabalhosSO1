#ifndef main_class_h
#define main_class_h

#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"
#include "Window.h"
#include "KbHandler.h"
#include "Engine.h"
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
        engineThread = new Thread(engineFunc);

        engineThread->join();
        windowThread->join();
        keyboardThread->join();

        delete engineThread;
        delete windowThread;
        delete keyboardThread;
    }

private:
    static void windowFunc()
    {
        windowObj = new Window(GameConfigs::windowWidth, GameConfigs::windowHeight, GameConfigs::fps);
        windowObj->run();
    }

    static void engineFunc()
    {
        engineObj = new Engine();
        engineObj->run();
    }

    static void keyBoardFunc()
    {
        kBoardObj = new KeyboardHandler();
        kBoardObj->run();
    }

    static Thread *engineThread;
    static Thread *windowThread;
    static Thread *keyboardThread;

    static Engine *engineObj;
    static Window *windowObj;
    static KeyboardHandler *kBoardObj;
};

__END_API

#endif
