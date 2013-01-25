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

#include "SDL_audio.h"
#include "SDL_mixer.h"

namespace Game {

extern Debug debug;

GameState::GameState():
loop(true),
outcome(IN_PROGRESS),

vampire(Location(400, 300)){

    // Populate people
    for (int i = 0; i != 10; ++i)
        personList.push_back(Person(Point(rand()%800, rand()%600)));

    

}

GameState::~GameState() {

	// Stop all channels
	Mix_HaltChannel(-1);
	
	/*while (!personList.empty()) {
		Person* p = personList.back();
		personList.pop_back();
		safe_delete(p);
	}*/

}

void GameState::draw() const {

}

} // namespace Game
