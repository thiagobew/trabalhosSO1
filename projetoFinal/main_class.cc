#include "include/main_class.h"

__BEGIN_API

Thread *Main::engineThread;
Thread *Main::windowThread;
Thread *Main::keyboardThread;

Engine *Main::engineObj;
Window *Main::windowObj;
KeyboardHandler *Main::kbObj;

__END_API
