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

    public:
        ucontext_t _context;

        Context() { _stack = 0; };

        template <typename... Tn>
        Context(void (*func)(Tn...), Tn... args);

        ~Context();

        void save();

        void load();
    };

    static void switch_context(Context *from, Context *to);
};

template <typename... Tn>
inline CPU::Context::Context(void (*func)(Tn...), Tn... args) {
    this->_stack = new char[this->STACK_SIZE];

    if (!this->_stack) {
        std::cout << "Error in creating stack\n";
        exit(-1);
    }

    save();

    // https://nitish712.blogspot.com/2012/10/thread-library-using-context-switching.html
    this->_context.uc_link = 0;
    this->_context.uc_stack.ss_sp = (void *)_stack;
    this->_context.uc_stack.ss_size = this->STACK_SIZE;
    this->_context.uc_stack.ss_flags = 0;

    makecontext(&this->_context, (void (*)())(func), sizeof...(Tn), args...);
};

__END_API

#endif
