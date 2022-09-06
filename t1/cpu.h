#ifndef cpu_h
#define cpu_h

#include "traits.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

class CPU {
public:
  class Context {
  private:
    static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
    char *_stack;
    void DefaultConstructor() {
      this->_stack = new char[this->STACK_SIZE];

      if (!this->_stack) {
        std::cout << "Erro ao alocar pilha\n";
        exit(1);
      }

      getcontext(&this->_context);
      this->_context.uc_link = 0;
      this->_context.uc_stack.ss_sp = (void *)_stack;
      this->_context.uc_stack.ss_size = this->STACK_SIZE;
      this->_context.uc_stack.ss_flags = 0;
    }

  public:
    ucontext_t _context;

    Context() { this->DefaultConstructor(); }

    template <typename... Tn> Context(void (*func)(Tn...), Tn... args) {
      this->DefaultConstructor();

      makecontext(&this->_context, (void (*)())(func), sizeof...(Tn), args...);
    };

    ~Context();

    void save();

    void load();
  };

  static void switch_context(Context *from, Context *to);
};

__END_API

#endif
