// (C) 2013 Tim Gurto

#include "Heart.h"
#include "Debug.h"
#include "util.h"

namespace Game {

	extern Debug debug;

	size_t Heart::nextId = AMBIENT_CHANNEL + 1;

	Heart::Heart(Mix_Chunk* b) :
		id(nextId),
		beat(b),
		playing(false),
		pauseTime(20.0),
		currPauseTime(0.0) {

		++nextId;
	}

	Heart::~Heart() {
	}

	void Heart::update(double delta) {

		// No music
		if (!beat) {
			return;
		}

		if (id > 1) {
			return;
		}

		// Start next beat playing?
		bool start = false;
		playing = Mix_Playing(id) == 1 ? true : false;
		if (!playing) {
			currPauseTime += delta;

			// Next beat
			if (currPauseTime > pauseTime) {
				start = true;
				currPauseTime = 0.0;
			}
		}

		if (start) {
			int success = Mix_PlayChannel(id, beat, 1) == 1 ? true : false;
			debug("play");
			if (success == -1) {
				debug("Could not play heartbeat");
			}
			playing = true;

			// The volume to use from 0 to MIX_MAX_VOLUME(128).
			/*success = Mix_VolumeChunk(beat, MIX_MAX_VOLUME) == 1 ? true : false;
			if (success == -1) {
				debug("Could not set heartbeat volume");
			}*/
		}

		// Music volume, from 0 to MIX_MAX_VOLUME(128).
		// Set after playing
		//success = Mix_VolumeMusic(MIX_MAX_VOLUME);
		//if (success == -1) {
		//	debug("Could not set heartbeat volume");
		//}

	}

} //namespace Game