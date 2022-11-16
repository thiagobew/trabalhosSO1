#ifndef semaphore_h
#define semaphore_h

#include "cpu.h"
#include "thread.h"
#include "traits.h"
#include "debug.h"
#include <queue>

__BEGIN_API

class Semaphore
{
public:
    typedef std::queue<Thread> Sleeping_Queue;
    Semaphore(int v = 1) : _value(v) {
            db<Semaphore>(TRC) << "Semaphore::Semaphore(" << v << ")\n";
    };
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
    Sleeping_Queue _sleeping;
    volatile int _value;
};

__END_API

#endif

