// (C) 2013 Tim Gurto

#ifndef AOE_ATTACK_H
#define AOE_ATTACK_H

#include "Entity.h"
#include "Sound.h"

namespace Game {

	class Person;
    struct GameState;

    class AOEAttack : public Entity{

        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

		// Time for the attack to run
		timer_t attackingTimer_;

		// Boom
		Sound missSound1_;
		Sound missSound2_;

    public:
		AOEAttack();

        static GameState *state;

        virtual bool isBatAttack() const;

		// Player wants to activate attack
		bool attackKeyIsActive_;

		virtual void update(double delta);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		// Hit a person if I am attacking and they are in range
		void attack(Person& person);
		void operator()(Person& person);

		// Start attack
		void activateFromPlayerInput(const Location& loc);

		virtual SDLKey getKey() const = 0;
		//virtual Sound& getSound() const = 0;

		bool isAttacking() const;
		bool attackSucceeded() const;
		bool attackFailed() const;
		void resetAttackState();

		virtual timer_t getCooldownTime() const = 0;
		virtual int getFailureCost() const = 0;
		virtual int getSuccessBonus() const = 0;

	protected:

		// Attack is in progress
		bool attacking_;

		// Set to true if the attack hits something while it is attacking
		bool attackHitSomething_;

		// Set to true after attack has finished if it hit something
		bool attackSucceeded_;

		// Set to true if the attack failed to hit anything after it is finished
		bool attackMissed_;

		virtual timer_t getAttackingTime() const = 0;
		virtual pixels_t getRadius() const = 0;
	};

} //namespace Game

#endif