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

  public:
    Context() {
      _stack = (char *)malloc(STACK_SIZE);

      if (!_stack) {
        std::cerr << "Error: could not allocate stack for context" << std::endl;
        exit(1);
      }
    }

    template <typename... Tn> Context(void (*func)(Tn...), Tn... an) {
      Context();
      getcontext(&_context);
      makecontext(&_context, (void (*)())(func), sizeof...(Tn), an...);
    };

    ~Context();

    void save();
    void load();

  private:
    char *_stack;

  public:
    ucontext_t _context;
  };

public:
  static void switch_context(Context *from, Context *to);
};

__END_API

#endif
