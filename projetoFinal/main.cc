#include "include/main_class.h"
#include "include/system.h"
#include "include/threads/thread.h"

__USING_API

int main(void)
{
   System::init(&Main::run);
}