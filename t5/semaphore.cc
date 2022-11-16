#include "semaphore.h"
#include "threads.h"
#include "cpu.h"

__BEGIN_API
// https://stackoverflow.com/questions/2545720/error-default-argument-given-for-parameter-1
// Parâmetros default só são definidos na declaração do método, não na implementação 

Semaphore::~Semaphore() {
    // Se o semáforo não estiver livre, então ele está bloqueado
    if (_value < 0) {
        // Desbloqueia todos os threads que estão esperando
        wakeup_all();
    }
}

// Tenta pegar o semáforo
void Semaphore::p() {
    // Decrementa o valor do semáforo
    CPU::fdec(_value);
    // Se o valor do semáforo for menor que 1, então o semáforo está bloqueado
    if (_value < 1) {
        // Bloqueia a thread
        sleep();
    }
}

// Libera o semáforo
void Semaphore::v() {
    asm("lock xadd %0, %2" : "=r"(_value) : "0"(1), "m"(_value));
    // Incrementa o valor do semáforo
    CPU::finc(_value);
    if (_value < 0) {
        // Desbloqueia a thread
        wakeup();
    }
}

void Semaphore::sleep() {
    // Pega uma referência da Thread running, a qual chamou esse método e irá dormir
    Thread* running = Thread::running();
    // A coloca na lista de threads dormindo
    _sleeping.push(*running);
    // Chama o método sleep de Thread que irá fazer as ações necessárias
    Thread::sleep();
}

void Semaphore::wakeup() {
    // Retira a primeria thread da fila de waiting
    Thread *sleepingThread = &_sleeping.front();
    _sleeping.pop();
    // Acorda a thread
    sleepingThread->wakeup();
}

void Semaphore::wakeup_all() {
    // Faz wakeUp de todas as threads que estão na fila de WAITING do semáforo
    while (_sleeping.size() > 0) {
        Thread* sleepingThread = &_sleeping.front();
        _sleeping.pop();
        sleepingThread->wakeup();
    }
}

// Talvez mover isso para uma classe Utils
int Semaphore::getTimestamp() {
    return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

__END_API