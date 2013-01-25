// (C) 2010-2011 Tim Gurto

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "Surface.h"
#include "Sound.h"
#include "Entity.h"
#include "Vampire.h"

namespace Game {

class Person;

struct GameState{

   bool loop; //whether or not to continue the game loop
   GameOutcome outcome; //the game's outcome/current status

   GameState();
   ~GameState();

   void init();

   void draw() const;

   Vampire vampire;

   const size_t numPeople;
   typedef std::vector<Person*> PersonList;
   PersonList personList;
};

} // namespace Game

#endif