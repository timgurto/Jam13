// (C) 2013 Tim Gurto

#include "BatAttack.h"

namespace Game {

	timer_t BatAttack::getAttackingTime() const {
		return 1000;
	}

	timer_t BatAttack::getCooldownTime() const {
		return 2000;
	}

	pixels_t BatAttack::getRadius() const {
		return 40;
	}

	SDLKey BatAttack::getKey() const {
		return SDLK_x;
	}

    void BatAttack::draw(Point offset, Surface &surface) const{
        
    }

} //namespace Game