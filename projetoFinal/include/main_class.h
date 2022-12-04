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
        engineThread = new Thread(engineFunc);
        windowThread = new Thread(windowFunc);
        keyboardThread = new Thread(keyBoardFunc);

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
        Main::windowObj->run();
    }

    static void engineFunc()
    {
        Main::engineObj->run();
    }

    static void keyBoardFunc()
    {
        Main::kbObj->run();
    }

    static Thread *engineThread;
    static Thread *windowThread;
    static Thread *keyboardThread;

    static Engine *engineObj;
    static Window *windowObj;
    static KeyboardHandler *kbObj;
};

__END_API

#endif
