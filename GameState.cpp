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

heartbeat(SOUND_PATH + "beat1.wav"),
offset(0, 0),

map(offset){

    // Populate people
    for (int i = 0; i != 3; ++i)
        personList.push_back(Person(Point(rand()%800, rand()%600)));

    Person::heartbeat = &heartbeat;

    map.tileSize = Point(40, 40);
    std::string TILES_PATH = IMAGE_PATH + "Tiles/";
    map.baseProportion = 0.9;
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
}

GameState::~GameState() {

    Person::heartbeat = 0;

    free(map.data);

	// Stop all channels
	Mix_HaltChannel(-1);
	
	/*while (!personList.empty()) {
		Person* p = personList.back();
		personList.pop_back();
		safe_delete(p);
	}*/

}

} // namespace Game
