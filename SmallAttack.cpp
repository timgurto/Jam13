// (C) 2013 Tim Gurto

#include "SmallAttack.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include <algorithm>
#include <cmath>

namespace Game {

    extern Debug debug;

	SmallAttack::SmallAttack() : sound(SOUND_PATH + "Ahhhh Breath.wav")
	{
	}

	timer_t SmallAttack::getAttackingTime() const {
		return 500;
	}

	timer_t SmallAttack::getCooldownTime() const {
		return 1000;
	}

	pixels_t SmallAttack::getRadius() const {
		return 40;
	}

	SDLKey SmallAttack::getKey() const {
		return SDLK_SPACE;
	}

	int SmallAttack::getJoyButton() const {
		return 0; // A
	}

	const Sound& SmallAttack::getHitSound() const {
		return sound;
	}

	int SmallAttack::getFailureCost() const {
		return -1;
	}

	int SmallAttack::getSuccessBonus() const {
		return 4;
	}

} //namespace Game