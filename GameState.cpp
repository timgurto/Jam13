// (C) 2010-2011 Tim Gurto

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include "Debug.h"
#include "globals.h"
#include "util.h"
#include "GameState.h"
#include "misc.h"
#include "Person.h"
#include "Screen.h"
#include "Map.h"
#include "AOEAttack.h"
#include "Environment.h"
#include "Blood.h"
#include "Vampire.h"

namespace Game {

extern Debug debug;

GameState::GameState():
loop(true),
outcome(IN_PROGRESS),

vampire(Location(1000, 1000)),

currPersonList(&personList1),

heartbeat(SOUND_PATH + "beat1.wav"),
offset(0, 0),
closestPerson(0),
heartTimer(rand()%200 + 900),

map(offset),

ahBreathSound(SOUND_PATH + "Ahhhh Breath.wav"),
deathBonesSound(SOUND_PATH + "DeathBones.wav"),
deathBonesScreamSound(SOUND_PATH + "DeathBonesScream.wav"),
deathScream(SOUND_PATH + "DeathScream.wav"),
evilSound(SOUND_PATH + "EVIL.WAV"),
miss1Sound(SOUND_PATH + "Miss.wav"),
miss2Sound(SOUND_PATH + "Miss2.wav"),
//slashSound(SOUND_PATH + "Slash_Sound_Effects_and_Music_006220237_prev.mp3"),

environment(vampire.getBloodPercent()),

shakingTime(0),
shakingMagnitude(0){

    Person::state = this;
    AOEAttack::state = this;
    Environment::state = this;
    Vampire::gameState = this;

    // Populate people
	const size_t maxPeople = MAX_CHANNELS;
	const size_t numPeople = 60;
	personList1.reserve(numPeople);
	personList2.reserve(numPeople);
    for (int i = 0; i != numPeople; ++i) {
        personList1.push_back(new Person(Point(rand()%1800 + 100, rand()%1800 + 100)));
	}

    map.tileSize = Point(40, 40);
    std::string TILES_PATH = IMAGE_PATH + "Tiles/";
    map.baseProportion = 0.93;
    map.tiles.push_back(TILES_PATH + "Grass.png"); //Important: first [0] is the base tile
    map.tiles.push_back(TILES_PATH + "Brick.png");
    map.tiles.push_back(TILES_PATH + "Brick2.png");
    map.tiles.push_back(TILES_PATH + "BrokenTombstone.png");
    map.tiles.push_back(TILES_PATH + "Dirt.png");
    map.tiles.push_back(TILES_PATH + "GrassRock.png");
    map.tiles.push_back(TILES_PATH + "GrassRockTile2.png");
    map.tiles.push_back(TILES_PATH + "Pebbles.png");
    map.tiles.push_back(TILES_PATH + "Slab.png");
    map.tiles.push_back(TILES_PATH + "Stick.png");
    map.tiles.push_back(TILES_PATH + "Stick2.png");
    map.tiles.push_back(TILES_PATH + "Tombstone.png");
    map.tiles.push_back(TILES_PATH + "Tombstone2.png");

    map.mapSize = Point(50, 50);
    map.randomize();

    size_t marginSize = 10; //ensures invisible borders
    leftBound = marginSize * map.tileSize.x;
    topBound = marginSize * map.tileSize.y;
    rightBound = (map.mapSize.x - marginSize) * map.tileSize.x;
    bottomBound = (map.mapSize.y - marginSize) * map.tileSize.y;

    std::string VAMPIRE_PATH = IMAGE_PATH + "Vampire/";
    idleE = Surface(VAMPIRE_PATH + "idleE.png", true);
    idleF = Surface(VAMPIRE_PATH + "idleF.png", true);
    idleG = Surface(VAMPIRE_PATH + "idleG.png", true);
    idleH = Surface(VAMPIRE_PATH + "idleH.png", true);
    Vampire::setIdleImages(&idleE, &idleF, &idleG, &idleH);
    movingE = Surface(VAMPIRE_PATH + "movingE.png", true);
    movingF = Surface(VAMPIRE_PATH + "movingF.png", true);
    movingG = Surface(VAMPIRE_PATH + "movingG.png", true);
    movingH = Surface(VAMPIRE_PATH + "movingH.png", true);
    Vampire::setMovingImages(&movingE, &movingF, &movingG, &movingH);
    attackingE = Surface(VAMPIRE_PATH + "attackingE.png", true);
    attackingF = Surface(VAMPIRE_PATH + "attackingF.png", true);
    attackingG = Surface(VAMPIRE_PATH + "attackingG.png", true);
    attackingH = Surface(VAMPIRE_PATH + "attackingH.png", true);
    Vampire::setAttackingImages(&attackingE, &attackingF, &attackingG, &attackingH);

    std::string deathsPath = IMAGE_PATH + "Death/";

   batDeaths.push_back(Death
       (deathsPath + "batkill.png", &deathScream, 20, 8, Point(128, 128), Point(33, 106)));
   batDeaths.push_back(Death
       (deathsPath + "batkill2.png", &deathScream, 20, 8, Point(128, 128), Point(90, 106)));

   closeDeaths.push_back(Death
       (deathsPath + "farmer_fall.png", &deathScream, 40, 8, Point(128, 128), Point(34, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "farmer_fall2.png", &deathScream, 40, 8, Point(128, 128), Point(91, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "gibletman.png", &deathScream, 41, 8, Point(256, 128), Point(125, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton.png", &deathBonesSound, 40, 8, Point(128, 128), Point(59, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton_blow_up.png", &deathBonesScreamSound, 40, 5, Point(384, 128), Point(29, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton_blow_up2.png", &deathBonesScreamSound, 40, 5, Point(384, 128), Point(352, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton2.png", &deathBonesSound, 40, 8, Point(128, 128), Point(68, 106)));

   // Health bar
   const std::string HEALTH_PATH = IMAGE_PATH + "HealthBar/";
   environment.healthBar_.negativeFillingBar = Surface(HEALTH_PATH + "Blue.png", true);
   environment.healthBar_.outlineBar = Surface(HEALTH_PATH + "Outline.png", true);
   environment.healthBar_.fullBar = Surface(HEALTH_PATH + "Red.png", true);
   environment.healthBar_.positiveFillingBar = Surface(HEALTH_PATH + "Yellow.png", true);


   bloodImages.push_back(Surface(IMAGE_PATH + "Death/blood0.png", true));
   bloodImages.push_back(Surface(IMAGE_PATH + "Death/blood1.png", true));
   bloodImages.push_back(Surface(IMAGE_PATH + "Death/blood2.png", true));
   bloodImages.push_back(Surface(IMAGE_PATH + "Death/blood3.png", true));
   bloodImages.push_back(Surface(IMAGE_PATH + "Death/blood4.png", true));
   bloodImages.push_back(Surface(IMAGE_PATH + "Death/blood5.png", true));
   bloodImages.push_back(Surface(IMAGE_PATH + "Death/blood6.png", true));

   Blood::images = &bloodImages;

}

GameState::~GameState() {

    free(map.data);

	// Stop all channels
	Mix_HaltChannel(-1);
	
	GameState::PersonList& currList = getPersonList();
	while (!currList.empty()) {
		Person* p = currList.back();
		currList.pop_back();
		safe_delete(p);
	}

}

const GameState::PersonList& GameState::getPersonList() const
{
	assert(currPersonList);
	return *currPersonList;
}

GameState::PersonList& GameState::getPersonList()
{
	assert(currPersonList);
	return *currPersonList;
}

GameState::PersonList& GameState::getTmpList()
{
	assert(currPersonList);
	if (currPersonList == &personList1) {
		return personList2;
	}
	else {
		return personList1;
	}
}

void GameState::swapPersonLists() {
	assert(currPersonList);
	GameState::PersonList& tmp = getTmpList();
	currPersonList->clear();
	currPersonList = &tmp;
}

bool GameState::isAllDead() const {
	return getPersonList().empty();
}


Death *GameState::getBatDeath(){
    return &batDeaths[rand() % batDeaths.size()];
}

Death *GameState::getCloseDeath(){
    return &closeDeaths[rand() % closeDeaths.size()];
}

void GameState::newVictim(const Victim &victim){
    victims.push_back(victim);
}

void GameState::shakeScreen(timer_t ms, pixels_t magnitude){
    shakingTime = max(shakingTime, ms);
    shakingMagnitude = max(shakingMagnitude, magnitude);
}

Location GameState::shakeOffset() const{
    Location l = offset;
    if (shakingTime > 0){
        l.x += (1.0 * rand() / RAND_MAX * shakingMagnitude) - shakingMagnitude/2;
        l.y += (1.0 * rand() / RAND_MAX * shakingMagnitude) - shakingMagnitude/2;
    }
    return l;
}

void GameState::reduceShakeTime(timer_t ms){
    if (shakingTime > ms)
        shakingTime -= ms;
    else
        shakingTime = 0;
}

} // namespace Game
