#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "debug.h"
#include "list.h"
#include "traits.h"
#include <chrono>
#include <ctime>

__BEGIN_API

class Thread {
protected:
    typedef CPU::Context Context;

public:
    typedef Ordered_List<Thread> Ready_Queue;

    // Thread State
    enum State {
        RUNNING,
        READY,
        FINISHING,
        SUSPENDED,
        WAITING
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */
    Thread() {}

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada
     * e os parâmetros passados para a função, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */
    template <typename... Tn>
    Thread(void (*entry)(Tn...), Tn... an);

    /*
     * Retorna a Thread que está em execução.
     */
    static Thread *running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */
    static int switch_context(Thread *prev, Thread *next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main.
     */
    void thread_exit(int exit_code);

    /*
     * Retorna o ID da thread.
     */
    int id() { return this->_id; }

    /*
     * NOVO MÉTODO DESTE TRABALHO.
     * Daspachante (disptacher) de threads.
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher();

    /*
     * NOVO MÉTODO DESTE TRABALHO.
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield();

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */
    ~Thread();

    /*
     * Qualquer outro método que você achar necessário para a solução.
     */
    int threads_quant() { return Thread::_next_id; }
    static int getTimestamp();

    int join();

    void suspend();

    void resume();

    // Método para fazer a thread dormir
    void sleep();

    // Acorda uma thread que estava dormindo 
    void wakeup();
    Ready_Queue::Element link() { return _link; }

  private:
    int _id;
    Context *volatile _context;
    static Thread *_running;

    static Thread _main;
    static CPU::Context _main_context;
    static Thread _dispatcher;
    static Ready_Queue _ready;
    Ready_Queue::Element _link;
    volatile State _state;

    /*
     * Qualquer outro atributo que você achar necessário para a solução.
     */
    static unsigned int _next_id;
    Thread* _awaitsJoin = nullptr;
    int _exit_code;
    static Ready_Queue _suspended;

    Context *context() { return _context; }
};

// https://stackoverflow.com/questions/1272680/what-does-a-colon-following-a-c-constructor-name-do
// O que está após os dois pontos se chama Initialization Lists, e servem para chamar construtores de base ou para instanciar atributos antes do construtuor começar
// Um exemplo é para setar variáveis const para cada instância da classe, essa ação só pode ser feita com initialization lists
template <typename... Tn>
inline Thread::Thread(void (*entry)(Tn...), Tn... an) : _link(this, Thread::getTimestamp()) {
    this->_context = new Context(entry, an...);
    this->_id = Thread::_next_id++;
    this->_state = Thread::State::READY;
    if (this->_id != 0) {
        Thread::_ready.insert(&_link);
    }

    db<Thread>(TRC) << "Thread " << this->_id << " created\n";
}

__END_API

#endif
