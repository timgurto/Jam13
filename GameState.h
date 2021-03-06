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
#include "Death.h"
#include "Victim.h"
#include "Blood.h"

#include "SDL_mixer.h"

namespace Game {

class Hunter;
class Person;

typedef std::vector<Death> deaths_t;
typedef std::vector<Victim> victims_t;

struct GameState{

   bool loop; //whether or not to continue the game loop
   GameOutcome outcome; //the game's outcome/current status

   GameState();
   ~GameState();

   Vampire vampire;

   Sound heartbeat;
   timer_t heartTimer;
   Person *closestPerson;

   Location offset;
   Map map;
   Environment environment;
   
   pixels_t
        leftBound,
        rightBound,
        topBound,
        bottomBound;

   typedef std::vector<Person*> PersonList;
   const PersonList& getPersonList() const;
   PersonList& getPersonList();
   PersonList& getTmpList();
   void swapPersonLists();
   bool isAllDead() const;

   deaths_t
       batDeaths,
       closeDeaths;
   victims_t
       victims;

   Death *getBatDeath();
   Death *getCloseDeath();

   void newVictim(const Victim &victim);

   void shakeScreen(timer_t ms, pixels_t magnitude);
   Location shakeOffset() const;
   void reduceShakeTime(timer_t ms);

   std::vector<Surface> bloodImages;
   std::vector<Blood> bloods;

   void startGameOverTimer(timer_t ms = 2500);

   timer_t gameOverTimer;


	Sound ahBreathSound;
	Sound deathBonesSound;
	Sound deathBonesScreamSound;
	Sound deathScream;
	Sound evilSound;
	Sound miss1Sound;
	Sound miss2Sound;

	Hunter* hunter;
    void setLevel(int level);

private:

	//Sound slashSound;

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
       movingH,
       attackingE,
       attackingF,
       attackingG,
       attackingH,
       burningL,
       burningR;

   timer_t shakingTime;
   pixels_t shakingMagnitude;
};

} // namespace Game

#endif