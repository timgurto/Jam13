// (C) 2013 Tim Gurto

#ifndef HUNTER_H
#define HUNTER_H

#include "Person.h"
#include "Sound.h"

namespace Game {

	class Hunter : public Person {
	public:
		Hunter(Point startPos);

		Sound hunterSound;
		Sound gunShotSound;

		virtual void update(double delta, pixels_t distToVamp);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		virtual void hit(int hitLife, bool isBatAttack) {}
		virtual bool isDead() const { return false; }

		bool attacking_;
		timer_t attackingTimer_;
	};

} //namespace Game

#endif