#include "semaphore.h"

__BEGIN_API

Semaphore::Semaphore(int v = 1)
{
    // Inicializa o semáforo com o valor v
    _value = v;
}

Semaphore::~Semaphore()
{
    // Se o semáforo não estiver livre, então ele está bloqueado
    if (_value < 0) {
        // Desbloqueia todos os threads que estão esperando
        wakeup_all();
    }
}

void Semaphore::p()
{
    // Decrementa o valor do semáforo
    fdec(_value);
    // Se o valor do semáforo for menor que 0, então o semáforo está bloqueado
    if (_value < 1) {
        // Bloqueia a thread
        sleep();
    }
}

void Semaphore::v()
{
    asm("lock xadd %0, %2" : "=r"(_value) : "0"(1), "m"(_value));
    // Incrementa o valor do semáforo
    finc(_value);
    if (_value < 0) {
        // Desbloqueia a thread
        wakeup();
    }
}

__END_API