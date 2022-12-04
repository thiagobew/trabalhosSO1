#ifndef ACTION_H
#define ACTION_H

#include "traits.h"

namespace act
{

   enum GameAction
   {
      NO_ACTION,
      MOVE_UP,
      MOVE_RIGHT,
      MOVE_DOWN,
      MOVE_LEFT,
      FIRE_PRIMARY,
      FIRE_SECONDARY,
      QUIT_GAME
   };

}
#endif
