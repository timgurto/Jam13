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

map(offset),

scream(SOUND_PATH + "boom1.wav") {

    // Populate people
	const size_t maxPeople = MAX_CHANNELS;
	const size_t numPeople = 3;
	personList1.reserve(numPeople);
	personList2.reserve(numPeople);
    for (int i = 0; i != numPeople; ++i) {
        personList1.push_back(new Person(Point(rand()%800, rand()%600)));
	}

    Person::heartbeat = &heartbeat;

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

}

GameState::~GameState() {

    Person::heartbeat = 0;

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

} // namespace Game
