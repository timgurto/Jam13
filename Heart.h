// (C) 2013 Tim Gurto

#ifndef HEART_H
#define HEART_H

#include "Entity.h"

#include "SDL_mixer.h"

namespace Game {

    class Heart {
	public:
		static size_t nextId;
		Heart(Mix_Chunk* b);
		~Heart();
		void update(double delta);
	private:
		Mix_Chunk* beat;
		bool playing;

		const size_t id;
		const double pauseTime;
		double currPauseTime;
	};

} //namespace Game

#endif