// (C) 2013 Tim Gurto

#ifndef BAT_ATTACK_H
#define BAT_ATTACK_H

#include "AOEAttack.h"

namespace Game {

	class BatAttack : public AOEAttack{

        int frameTime;

        mutable Surface image;

	public:
		virtual SDLKey getKey() const;
		//virtual Sound& getSound() const;

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

        virtual void update(double delta);

        size_t frame;
        static const size_t FRAMES;
        static const size_t COLUMNS;
        static const Point DIM;

        BatAttack();

        virtual bool isBatAttack();

	protected:
		virtual timer_t getAttackingTime() const;
		virtual timer_t getCooldownTime() const;
		virtual pixels_t getRadius() const;
		virtual int getFailureCost() const;
		virtual int getSuccessBonus() const;
	};

} //namespace Game

#endif