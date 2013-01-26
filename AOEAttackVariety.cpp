// (C) 2013 Tim Gurto

#include "AOEAttackVariety.h"
#include "util.h"
#include "Debug.h"
#include "Person.h"
#include <algorithm>
#include <cmath>

namespace Game {

    extern Debug debug;

	// Small
	timer_t SmallAOEAttack::getAttackingTime() const {
		return 500;
	}

	timer_t SmallAOEAttack::getCooldownTime() const {
		return 1000;
	}

	pixels_t SmallAOEAttack::getRadius() const {
		return 20;
	}

	SDLKey SmallAOEAttack::getKey() const {
		return SDLK_z;
	}

    //void SmallAOEAttack::draw(Point offset, Surface &surface) const{
    //    
    //}


} //namespace Game