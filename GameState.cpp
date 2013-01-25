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
vampire(Location(400, 300)),
numPeople(10),
music(0),
beat(0)
{}

GameState::~GameState() {

	// Stop all channels
	Mix_HaltChannel(-1);
	
	while (!personList.empty()) {
		Person* p = personList.back();
		personList.pop_back();
		safe_delete(p);
	}

	if (beat) {
		Mix_FreeChunk(beat);
	}

	
	if (music) {
		Mix_FreeMusic(music);
	}
}

// Called after Screen is initialised
void GameState::init() {

	// - Sounds
	// Channels
	int Mix_AllocateChannels(MAX_CHANNELS);

	// Ambient
		
	// load the MP3 file "music.mp3" to play as music
	/*music = Mix_LoadMUS( (SOUND_PATH + "wolfram.ambient.31.1793131581.mid").c_str() );
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
	beat = Mix_LoadWAV( (SOUND_PATH + "beat1.wav").c_str() );
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

void GameState::draw() const {
    ITERATE(PersonList::const_iterator, personList, itr){
		const Person* p = *itr;
		assert(p);
		p->draw();
	}
}

} // namespace Game
