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
numPeople(10),
music(0),
beat(0)
{}

GameState::~GameState() {
	if (music) {
		Mix_FreeMusic(music);
	}
	while (!personList.empty()) {
		Person* p = personList.back();
		personList.pop_back();
		safe_delete(p);
	}
	if (beat) {
		Mix_FreeMusic(beat);
	}
}

// Called after Screen is initialised
void GameState::init() {

	// - Sounds
	// Ambient
		
	// load the MP3 file "music.mp3" to play as music
	/*music = Mix_LoadMUS("Sounds/wolfram.ambient.31.1793131581.mid");
	if(!music) {
		debug("Could not load ambient music: ", Mix_GetError());
	}
	if (music) {
		int success;

		success = Mix_PlayMusic(music, -1);
		if (success == -1) {
			debug("Could not play music");
		}

		// Music volume, from 0 to MIX_MAX_VOLUME(128).
		// Set after playing
		success = Mix_VolumeMusic(59);
		if (success == -1) {
			debug("Could not set music volume");
		}

	}*/

	// Heart
		
	// load the MP3 file "music.mp3" to play as music
	Mix_Music* beat = Mix_LoadMUS("Sounds/beat1.wav");
	if(!beat) {
		debug("Could not load heartbeat: ", Mix_GetError());
	}

	// Populate people
	const Point& screenRes = Screen::getScreenRes();

	personList.resize(numPeople);
	for (size_t i = 0; i < numPeople; ++i) {
		const Point pos(rand() % screenRes.x, rand() % screenRes.y);
		personList[i] = new Person(pos, beat);
	}
	
}

void GameState::update(double delta) {
	PersonList::iterator itr;
	for (itr = personList.begin(); itr != personList.end(); ++itr) {
		Person* p = *itr;
		assert(p);
		p->update(delta);
	}
}

void GameState::draw() const {
	PersonList::const_iterator itr;
	for (itr = personList.begin(); itr != personList.end(); ++itr) {
		const Person* p = *itr;
		assert(p);
		p->draw();
	}
}

} // namespace Game
