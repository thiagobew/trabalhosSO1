#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API    \
    namespace SOLUTION \
    {
#define __END_API }
#define __USING_API using namespace SOLUTION;

__BEGIN_API

class CPU; // declaração das classes criadas nos trabalhos devem ser colocadas
           // aqui
class Debug;

class Thread;

class System;

class Main;

class Lists;

class Semaphore;

class Engine;

class KeyboardHandler;

class Window;

template <typename T>
struct Traits
{
    // Booleano para permitir o print das mensagens ou não, por padrão está bloqueado para todas as classes
    static const bool debugged = true;
};

template <>
struct Traits<CPU>
{
    static const int STACK_SIZE = 0x10000;
    static const bool debugged = true;
};

template <>
struct Traits<Main>
{
    static const bool debugged = true;
};

template <>
struct Traits<Semaphore>
{
    static const bool debugged = false;
};

template <>
struct Traits<Lists>
{
    static const bool debugged = false;
};

template <>
struct Traits<Debug> : public Traits<void>
{
    // Em Debug podemos habilitar ou desabilitar os tipos de debug, nesse caso somente tipos INF serão printados
    static const bool error = true;
    static const bool warning = true;
    static const bool info = true;
    static const bool trace = true;
};

template <>
struct Traits<System> : public Traits<void>
{
    static const bool debugged = true;
};

template <>
struct Traits<Thread> : public Traits<void>
{
    // Nessa classe ocorre um override, permitindo print de mensagens dentro de Thread
    static const bool debugged = true;
};

template <>
struct Traits<Window> : public Traits<void>
{
    static const bool debugged = true;
};

template <>
struct Traits<Engine> : public Traits<void>
{
    static const bool debugged = true;
};

template <>
struct Traits<KeyboardHandler> : public Traits<void>
{
    static const bool debugged = true;
};

__END_API

#endif
