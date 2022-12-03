/*

#include "include/Window.h"
#include "include/Engine.h"
#include "include/thread.h"
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

int main()
{
   srand(time(0));

   Engine shooty(800, 600, 60);
   shooty.init();
   shooty.run();

   return 0;
}
 */

#include "include/main_class.h"
#include "include/system.h"
#include "include/thread.h"

__USING_API

int main(void)
{
   System::init(&Main::run);
}