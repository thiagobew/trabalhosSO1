#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API namespace SOLUTION {
#define __END_API }
#define __USING_API using namespace SOLUTION;

__BEGIN_API

class CPU; // declaração das classes criadas nos trabalhos devem ser colocadas
           // aqui
class Debug;

class Thread;

class System;

// declaração da classe Traits
// Verificar se essa variável está sendo settada para todas as classes e nas declarações
// específicas está ocorrendo um override
template <typename T>
struct Traits {
    static const bool debugged = true;
};

template <>
struct Traits<CPU> {
    static const int STACK_SIZE = 0x10000;
};

template <>
struct Traits<Debug> : public Traits<void> {
    static const bool error = false;
    static const bool warning = false;
    static const bool info = true;
    static const bool trace = true;
};

template <>
struct Traits<System> : public Traits<void> {
    static const bool debugged = true;
};

__END_API

#endif
