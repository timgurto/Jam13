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

namespace Game {

extern Debug debug;

GameState::GameState():
loop(true),
outcome(IN_PROGRESS),

vampire(Location(400, 300)),

currPersonList(&personList1),

heartbeat(SOUND_PATH + "beat1.wav"),
offset(0, 0),
closestPerson(0),
heartTimer(rand()%200 + 900),

map(offset),

scream(SOUND_PATH + "death1.wav"),

environment(vampire.getTotalBlood()),
overlay(IMAGE_PATH + "Overlay.png", true){

    Person::state = this;

    // Populate people
	const size_t maxPeople = MAX_CHANNELS;
	const size_t numPeople = 6;
	personList1.reserve(numPeople);
	personList2.reserve(numPeople);
    for (int i = 0; i != numPeople; ++i) {
        personList1.push_back(new Person(Point(rand()%800, rand()%600)));
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

    map.mapSize = Point(30, 20);
    map.randomize();

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
       (deathsPath + "batkill.png", 20, 8, Point(128, 128), Point(33, 106)));
   batDeaths.push_back(Death
       (deathsPath + "batkill2.png", 20, 8, Point(128, 128), Point(90, 106)));

   closeDeaths.push_back(Death
       (deathsPath + "farmer_fall.png", 40, 8, Point(128, 128), Point(34, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "farmer_fall2.png", 40, 8, Point(128, 128), Point(91, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "gibletman.png", 41, 8, Point(256, 128), Point(125, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton.png", 40, 8, Point(128, 128), Point(59, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton_blow_up.png", 40, 5, Point(384, 128), Point(29, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton_blow_up2.png", 40, 5, Point(384, 128), Point(352, 106)));
   closeDeaths.push_back(Death
       (deathsPath + "skeleton2.png", 40, 8, Point(128, 128), Point(68, 106)));

   //victims.push_back(Victim(Location(380, 350), &closeDeaths[2]));
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

void GameState::soundScream() {
	scream.play(-1, 0);
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

} // namespace Game
