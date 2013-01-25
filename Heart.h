// (C) 2013 Tim Gurto

#ifndef HEART_H
#define HEART_H

#include "Entity.h"

#include "SDL_mixer.h"

namespace Game {

    class Heart {
	public:
		Heart(Mix_Music* b);
		~Heart();
		void update(double delta);
	private:
		Mix_Music* beat;
		bool playing;

		const double pauseTime;
		double currPauseTime;
	};

} //namespace Game

#endif