#ifndef window_h
#define window_h

#include "traits.h"
#include <stdio.h>

__BEGIN_API

// Classe para desenhar as coisas na tela
class Window
{
public:
    Window();
    ~Window();
    
    void draw();
    static void init(void (*main)(void *));
};

__END_API

#endif