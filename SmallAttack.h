// (C) 2013 Tim Gurto

#ifndef SMALL_ATTACK_H
#define SMALL_ATTACK_H

#include "AOEAttack.h"
#include "Sound.h"

namespace Game {

	// Small
    class SmallAttack : public AOEAttack{

	public:
		SmallAttack();

		virtual SDLKey getKey() const;
		virtual const Sound& getHitSound() const;
		virtual timer_t getCooldownTime() const;
		virtual int getFailureCost() const;
		virtual int getSuccessBonus() const;

	protected:
		virtual timer_t getAttackingTime() const;
		virtual pixels_t getRadius() const;

	private:
		Sound sound;
	};


} //namespace Game

#endif