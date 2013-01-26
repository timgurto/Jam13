// (C) 2013 Tim Gurto

#include "SmallAttack.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include <algorithm>
#include <cmath>

namespace Game {

    extern Debug debug;

	// Small
	timer_t SmallAttack::getAttackingTime() const {
		return 500;
	}

	timer_t SmallAttack::getCooldownTime() const {
		return 1000;
	}

	pixels_t SmallAttack::getRadius() const {
		return 20;
	}

	SDLKey SmallAttack::getKey() const {
		return SDLK_z;
	}

    void SmallAttack::draw(Point offset, Surface &surface) const{
        // Nothing - vampire animates instead

		if (DEBUG) {
			AOEAttack::draw(offset, surface);
		}
    }

	int SmallAttack::getFailureCost() const {
		return -1;
	}

	int SmallAttack::getSuccessBonus() const {
		return 3;
	}

} //namespace Game