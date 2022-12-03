#ifndef main_class_h
#define main_class_h

#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"
#include "Window.h"
#include "Engine.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>

__BEGIN_API

class Main
{
public:
    Main() {}
    ~Main() {}

    // Essa função será passada para Thread::init()
    static void run(void *name)
    {
        std::cout << (char *)name << ": inicio\n";

        threads[0] = new Thread(engineThread);
        threads[1] = new Thread(windowThread);
        
        threads[0]->join();
        threads[0]->join();


        delete threads[0];
    }

private:
    static void windowThread();

    static void engineThread()
    {
        srand(time(0));
        // Cria a engine
        Engine shooty(800, 600, 60);
        shooty.init();
        shooty.run();
    }

    static Thread *threads[5];
    static Semaphore *sem;
};

__END_API

#endif
