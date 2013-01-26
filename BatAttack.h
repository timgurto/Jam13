// (C) 2013 Tim Gurto

#ifndef BAT_ATTACK_H
#define BAT_ATTACK_H

#include "AOEAttack.h"

namespace Game {

	class BatAttack : public AOEAttack{

	public:
		virtual SDLKey getKey() const;
		//virtual Sound& getSound() const;

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

	protected:
		virtual timer_t getAttackingTime() const;
		virtual timer_t getCooldownTime() const;
		virtual pixels_t getRadius() const;
	};

} //namespace Game

#endif