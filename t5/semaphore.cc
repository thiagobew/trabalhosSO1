#include "semaphore.h"
#include "threads.h"
#include "cpu.h"

__BEGIN_API

Semaphore::~Semaphore() {
    // Se o semáforo não estiver livre, então ele está bloqueado
    if (_value < 0) {
        // Desbloqueia todos os threads que estão esperando
        wakeup_all();
    }
}

// Tenta pegar o semáforo
void Semaphore::p() {
    db<Semaphore>(TRC) << "Semaphore before p(): " << _value << "\n";
    // Se o valor do semáforo for menor que 1, então o semáforo está bloqueado
    if (CPU::fdec(_value) < 1) {
        // Bloqueia a thread
        sleep();
    }
    db<Semaphore>(TRC) << "Semaphore after p(): " << _value << "\n";
}

// Libera o semáforo
void Semaphore::v() {
    db<Semaphore>(TRC) << "Semaphore before v(): " << _value << "\n";
    // Incrementa o valor do semáforo
    if (CPU::finc(_value) < 0) {
        // Desbloqueia a thread
        wakeup();
    }
    db<Semaphore>(TRC) << "Semaphore after v(): " << _value << "\n";
}

void Semaphore::sleep() {
    // Pega uma referência da Thread running, a qual chamou esse método e irá dormir
    Thread* running = Thread::running();
    // A coloca na lista de threads dormindo
    _sleeping.push(*running);
    // Chama o método sleep de Thread que irá fazer as ações necessárias
    running->sleep();
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