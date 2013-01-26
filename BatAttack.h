// (C) 2013 Tim Gurto

#ifndef BAT_ATTACK_H
#define BAT_ATTACK_H

#include "AOEAttack.h"

namespace Game {

	class BatAttack : public AOEAttack{
	public:
		BatAttack();

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;
        virtual void update(double delta);

        virtual bool isBatAttack() const;

		virtual SDLKey getKey() const;
		virtual int getJoyButton() const;
		virtual const Sound& getHitSound() const;
		virtual timer_t getCooldownTime() const;
		virtual int getFailureCost() const;
		virtual int getSuccessBonus() const;

        static const size_t FRAMES;
        static const size_t COLUMNS;
        static const Point DIM;

	protected:
		virtual timer_t getAttackingTime() const;
		virtual pixels_t getRadius() const;
	private:
		mutable Surface image;
		Sound sound;
		size_t frame;
        int frameTime;
	};

} //namespace Game

#endif