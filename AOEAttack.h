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

    public:
		AOEAttack();

        static GameState *state;

        virtual bool isBatAttack() const;

		virtual void update(double delta);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		// Hit a person if I am attacking and they are in range
		void hitAttacks(Person& person);
		void operator()(Person& person);

		bool attackSucceeded() const;
		size_t getNumHit() const;
		void playAttackSuccess();
		void playAttackFail();

		// Start attack
		virtual void play(const Location& loc);
		bool isPlaying() const;

		// Attack has been played but animation is finishing
		bool isAnimationPlaying() const;

		virtual SDLKey getKey() const = 0;
		virtual int getJoyButton() const = 0;
		virtual const Sound& getHitSound() const = 0;
		virtual timer_t getCooldownTime() const = 0;
		virtual int getFailureCost() const = 0;
		virtual int getSuccessBonus() const = 0;

	protected:
		virtual timer_t getAttackingTime() const = 0;
		virtual pixels_t getRadius() const = 0;

		// Time for the attack to run
		timer_t attackingTimer_;

		bool playing_;
		size_t numHit_;

		Sound missSound1_;
		Sound missSound2_;
	};

} //namespace Game

#endif