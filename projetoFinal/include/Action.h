#ifndef ACTION_H
#define ACTION_H

#include "traits.h"

__BEGIN_API

namespace act
{

   enum KbKey
   {
      MOVE_UP,
      MOVE_DOWN,
      MOVE_RIGHT,
      MOVE_LEFT,
      SPACE,
      NUM_1,
      ESC
   };

   enum GameAction
   {
      NO_ACTION,
      FIRE_PRIMARY,
      FIRE_SECONDARY,
      QUIT_GAME
   };
}

__END_API

#endif
