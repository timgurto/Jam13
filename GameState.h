// (C) 2010-2011 Tim Gurto

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "Surface.h"
#include "Sound.h"
#include "Entity.h"
#include "Environment.h"
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

   void soundScream();

   Vampire vampire;

   Sound heartbeat;

   Location offset;
   Map map;
   Environment environment;

   typedef std::vector<Person*> PersonList;
   const PersonList& getPersonList() const;
   PersonList& getPersonList();
   PersonList& getTmpList();
   void swapPersonLists();
   bool isAllDead() const;

private:
	Sound scream;
   PersonList* currPersonList;
   PersonList personList1;
   PersonList personList2;

   Surface
       idleE,
       idleF,
       idleG,
       idleH,
       movingE,
       movingF,
       movingG,
       movingH;
};

} // namespace Game

#endif