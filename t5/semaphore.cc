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
    if (_value <= 0) {
        // Verificar utilidade do retorno
        // Bloqueia a thread
        sleep();
    } 

    CPU::fdec(_value);
    db<Semaphore>(TRC) << "Semaphore after p(): " << _value << "\n";
}

// Libera o semáforo
void Semaphore::v() {
    db<Semaphore>(TRC) << "Semaphore before v(): " << _value << "\n";
    // Caso semáforo esteja bloqueado
    if (_value <= 0) {
        // Incrementa o valor do semáforo
        CPU::finc(_value);
        // Desbloqueia a thread
        wakeup();
    } else {
        CPU::finc(_value);
    }

    db<Semaphore>(TRC) << "Semaphore after v(): " << _value << "\n";
}

void Semaphore::sleep() {
    // Pega uma referência da Thread running, a qual chamou esse método e irá dormir
    Thread* running = Thread::running();
    // A coloca na lista de threads dormindo
    _sleeping.push(running);
    // Chama o método sleep de Thread que irá fazer as ações necessárias
    running->sleep();
}

void Semaphore::wakeup() {
    if (_sleeping.empty())
        return;

    // Pega uma referência da primeira da fila
    Thread *sleepingThread = _sleeping.front();
    // Remove a primeira da fila
    _sleeping.pop();    
    // Acorda a thread
    sleepingThread->wakeup();
}

void Semaphore::wakeup_all() {
    // Faz wakeUp de todas as threads que estão na fila de WAITING do semáforo
    while (!_sleeping.empty()) {
        Thread* sleepingThread = _sleeping.front();
        _sleeping.pop();
        sleepingThread->wakeup();
    }
}

// Talvez mover isso para uma classe Utils
int Semaphore::getTimestamp() {
    return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

__END_API