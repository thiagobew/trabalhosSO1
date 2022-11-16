#include "thread.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

// Fazendo a next_id começar com 0, essa variável também mostra quantas threads existem no momento
unsigned int Thread::_next_id = 0;

// https://stackoverflow.com/questions/9110487/undefined-reference-to-a-static-member
// Precisamos declarar as variáveis staticas no arquivo .cpp
Thread *Thread::_running;
Thread Thread::_main;
CPU::Context Thread::_main_context;
Thread Thread::_dispatcher;
Thread::Ready_Queue Thread::_ready;
Thread::Ready_Queue Thread::_suspended;

int Thread::join() {
    if (_running == this) {
        db<Thread>(WRN) << "Thread::join: trying to join itself!" << "\n";
        return -1;
    }

    if (_awaitsJoin) {
        db<Thread>(WRN) << "Thread::join: thread already waiting for join!" << "\n";
        return -1;
    }

    if (_state != FINISHING) {
      _awaitsJoin = _running;
      _running->suspend();
    }

    return _exit_code;
}

void Thread::suspend() {
  this->_state = SUSPENDED;
  _suspended.insert(&_link);
  if (this != _running) {
    _ready.remove(&_link);
  } else {
    yield();
  }
}

void Thread::resume() {
    // remove se estiver na fila (senão não faz nada)
    _suspended.remove(this);
    _state = READY;
    _ready.insert(&_link);
}

int Thread::switch_context(Thread *prev, Thread *next) {
    return CPU::switch_context(prev->context(), next->context());
};

// Este método irá então criar a Thread main, passando como parâmetro para o contexto o
// ponteiro da função main recebido como argumento
void Thread::init(void (*main)(void *)) {
    // Cria a main thread
    new (&_main) Thread(main, (void *)"Main");
    _running = &_main;
    _main._state = RUNNING;
    // Cria o dispatcher
    new (&_dispatcher) Thread(&dispatcher);
    // Pega contexto atual para passar a Main
    new (&_main_context) CPU::Context();

    CPU::switch_context(&_main_context, _main.context());
};

int Thread::getTimestamp() {
    return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

void Thread::dispatcher() {
    while (!_ready.empty()) {
        db<Thread>(TRC) << "List size: " << _ready.size() << "\n";
        // Retira próxima thread a ser executada
        Thread *next = _ready.remove_head()->object();
        // Altera o estado do escalonador
        _dispatcher._state = READY;

        // insert insere ordenado (importante para manter prioridade)
        _ready.insert(&_dispatcher._link);
        _running = next;
        next->_state = RUNNING;
        switch_context(&_dispatcher, next);

        if (!_ready.empty() > 0 && _ready.head()->object()->_state == FINISHING) {
            _ready.remove_head();
        }
    }
    db<Thread>(TRC) << "Out of dispatcher while\n";
    _dispatcher._state = FINISHING;
    switch_context(&_dispatcher, &_main);
}

void Thread::yield() {
    Thread *next = _ready.remove_head()->object();
    Thread *prev = _running;
    db<Thread>(TRC) << "Running state: " << prev->_state << "\n";
    if (_running != &_main && _running->_state != FINISHING && _running->_state != SUSPENDED && _running->_state != WAITING) {
        _running->_link.rank(getTimestamp());
        _running->_state = READY;
        _ready.insert(&_running->_link);
        db<Thread>(TRC) << "Thread " << _running->_id << " reinserted in list"
                        << "\n";
    }

    _running = next;
    next->_state = RUNNING;
    db<Thread>(TRC) << "Switch " << prev->id() << " -> " << next->id() << "\n";
    switch_context(prev, next);
}

Thread::~Thread() {
    _ready.remove(&this->_link);
    if (this->_context)
        delete this->_context;
}

void Thread::sleep() {
    // Coloca a thread running como WAITING e faz o yield para passar a execução para a próxima
    _state = WAITING;
    if (_running != this) {
      _ready.remove(&_link);
    } else {
        yield();
    }

}

void Thread::wakeup() {
    // Seta o state como READY e o recoloca na fila de Ready
    this->_state = READY;
    this->_link.rank(getTimestamp());
    this->_ready.insert(&this->_link);

}

void Thread::thread_exit(int exit_code) {
    // Decrementa o next_id para saber quantas Threads ativas existem no SO
    _next_id -= 1;
    this->_state = FINISHING;
    this->_exit_code = exit_code;
    if (this->_awaitsJoin != nullptr) {
        this->_awaitsJoin->resume();
        this->_awaitsJoin = nullptr;
    }
    yield();
};

__END_API
