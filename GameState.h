// (C) 2010-2011 Tim Gurto

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "Surface.h"
#include "Sound.h"
#include "Entity.h"
#include "Vampire.h"
#include "Map.h"

#include "SDL_mixer.h"

namespace Game {

class Person;

struct GameState{

   bool loop; //whether or not to continue the game loop
   GameOutcome outcome; //the game's outcome/current status

   GameState();
   ~GameState();

   Vampire vampire;

   typedef std::vector<Person> PersonList;
   PersonList personList;

   Sound heartbeat;

   Location offset;
   Map map;

   Surface
       idleE,
       idleF,
       idleG,
       idleH;
};

} // namespace Game

#endif