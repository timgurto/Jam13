// (C) 2013 Tim Gurto

#include "Heart.h"
#include "Debug.h"
#include "util.h"

namespace Game {

	extern Debug debug;

	Heart::Heart(Mix_Music* b) :
		beat(b),
		playing(false),
		pauseTime(3.0),
		currPauseTime(0.0) {
	}
	Heart::~Heart() {
	}

	void Heart::update(double delta) {

		// No music
		if (!beat) {
			return;
		}

		// Start next beat playing?
		bool start = false;
		playing = Mix_PlayingMusic();
		if (!playing) {
			currPauseTime += delta;

			// Next beat
			if (currPauseTime > pauseTime) {
				start = true;
				currPauseTime = 0.0;
			}
		}

		if (start) {
			int success = Mix_PlayMusic(beat, 1);
			if (success == -1) {
				debug("Could not play heartbeat");
			}
			playing = true;
		}

		// Music volume, from 0 to MIX_MAX_VOLUME(128).
		// Set after playing
		//success = Mix_VolumeMusic(MIX_MAX_VOLUME);
		//if (success == -1) {
		//	debug("Could not set heartbeat volume");
		//}

	}

} //namespace Game