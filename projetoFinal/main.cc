#include "include/SpaceShooter.h"
#include "include/system.h"
#include "include/threads/thread.h"

__USING_API

int main(void)
{
   System::init(&SpaceShooter::run);
}