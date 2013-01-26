// (C) 2013 Tim Gurto

#ifndef AOE_ATTACK_VARIETY_H
#define AOE_ATTACK_VARIETY_H

#include "AOEAttack.h"
#include "Sound.h"

namespace Game {

	// Small
    class SmallAOEAttack : public AOEAttack{

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