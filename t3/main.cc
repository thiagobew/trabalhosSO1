#include "main_class.h"
#include "system.h"
#include "thread.h"

__USING_API

int main(void) {
    System::init();
    Main *m = new Main();
    delete m;
}