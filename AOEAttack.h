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

		bool active_;

    public:
		AOEAttack();

		virtual void update(double delta);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		// Hit a person if I am attacking and they are in range
		void attack(Person& person) const;
		void operator()(Person& person) const;

		// Start attack
		void activate(const Location& loc);

		// Stop attack
		void deactivate();
	};

} //namespace Game

#endif