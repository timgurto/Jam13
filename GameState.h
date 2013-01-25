// (C) 2010-2011 Tim Gurto

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "Surface.h"
#include "Sound.h"
#include "Entity.h"
#include "Vampire.h"

namespace Game {

struct GameState{

   bool loop; //whether or not to continue the game loop
   GameOutcome outcome; //the game's outcome/current status

   GameState();

   Vampire vampire;

};

} // namespace Game

#endif