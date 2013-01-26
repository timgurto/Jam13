// (C) 2013 Tim Gurto

#ifndef AOE_ATTACK_H
#define AOE_ATTACK_H

#include "Entity.h"
#include "Sound.h"

namespace Game {

	class Person;

    class AOEAttack : public Entity{

        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

		// Player wants to activate attack
		bool active_;

		// Attack is in progress
		bool attacking_;

		// Time for the attack to run
		timer_t attackingTimer_;

		// Time before you can activate the attack again
		// counted from the start of the attack activation
		timer_t cooldownTimer_;

		// Circular collision
		pixels_t radius_;

		// Boom
		Sound sound_;

		// Blood absorbed
		int blood_;

    public:
		static const timer_t ATTACKING_TIME;
		static const timer_t COOLDOWN_TIME;

		AOEAttack();

		virtual void update(double delta);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		// Hit a person if I am attacking and they are in range
		void attack(Person& person);
		void operator()(Person& person);

		// Start attack
		void activate(const Location& loc);

		// Stop attack
		void deactivate();
	};

} //namespace Game

#endif