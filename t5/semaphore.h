#ifndef semaphore_h
#define semaphore_h

#include "cpu.h"
#include "thread.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class Semaphore
{
public:
    Semaphore(int v = 1);
    ~Semaphore();

    void p();
    void v();
private:
    // Atomic operations
    int finc(volatile int & number);
    int fdec(volatile int & number);

    // Thread operations
    void sleep();
    void wakeup();
    void wakeup_all();
    int getTimestamp();

private:
    // Lista de threads sleeping no semáforo
    Ready_Queue _sleeping;
    // Elento da Ready_Queue
    Ready_Queue::Element _link;
    volatile int _value;
};

__END_API

#endif

