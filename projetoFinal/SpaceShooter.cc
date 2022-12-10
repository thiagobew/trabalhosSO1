#include "include/SpaceShooter.h"

__BEGIN_API

Thread *SpaceShooter::playerShipThread;
Thread *SpaceShooter::windowThread;
Thread *SpaceShooter::keyboardThread;
Thread *SpaceShooter::collisionThread;
Thread *SpaceShooter::purpleShipsControlThread;
Thread *SpaceShooter::minesControlThread;

PlayerShip *SpaceShooter::playerShipObj;
Window *SpaceShooter::windowObj;
Keyboard *SpaceShooter::kBoardObj;
Collision *SpaceShooter::collisionObj;
PurpleEnemiesControl *SpaceShooter::purpleShipsControlObj;
MinesControl *SpaceShooter::minesControlObj;

__END_API
