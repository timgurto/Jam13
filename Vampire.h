// (C) 2013 Tim Gurto

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Entity.h"
#include "SmallAttack.h"
#include "BatAttack.h"

namespace Game {

	class Person;
    class GameState;

    class Vampire : public Entity{

        enum Direction{
            DIR_U,
            DIR_D,
            DIR_L,
            DIR_R,
            DIR_E,
            DIR_F,
            DIR_G,
            DIR_H
        };

        enum VampireState{
            IDLE,
            MOVING,
            ATTACKING
        };

        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

        static const double SPEED;

        static const Surface
            *idleE,
            *idleF,
            *idleG,
            *idleH,
            *movingE,
            *movingF,
            *movingG,
            *movingH,
            *attackingE,
            *attackingF,
            *attackingG,
            *attackingH;

        const static size_t
            idleColumns,
            idleFrames,
            movingColumns,
            movingFrames,
            attackingColumns,
            attackingFrames;

        timer_t frameTime; //time until next frame.  Resets at 42ms (~24f/s)
        size_t frame; //current frame

        VampireState state;

		SmallAttack smallAttack;
		BatAttack batAttack;

		// Health of vampire
		double totalBlood_;

		// Time before you can activate the attack again
		// counted from the start of the attack activation
		timer_t cooldownTimer_;

    public:

        static GameState *gameState;

		static const double MAX_HEALTH;

        Vampire(const Location &loc);

		double getTotalBlood() const;
		double getBloodPercent() const;
		bool isDead() const;
		bool isBloodFull() const;

        SDL_Rect getDrawRect(Point offset) const;

        SDL_Rect getCollisionRect(Point offset) const;

        static void setIdleImages(const Surface *e,
                                  const Surface *f,
                                  const Surface *g,
                                  const Surface *h);

        static void setMovingImages(const Surface *e,
                                    const Surface *f,
                                    const Surface *g,
                                    const Surface *h);

        static void setAttackingImages(const Surface *e,
                                       const Surface *f,
                                       const Surface *g,
                                       const Surface *h);

		void updateDirection(Direction newDir);

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;
        void update(double delta);

		bool checkInputForAttacks();
		void hitAttacks(Person& p);
		void scoreAttacks();

		bool attackSucceeded() const;
		void playAttackSuccess();
		void playAttackFail();

		Direction lastUpDown;
        Direction lastLeftRight;
        Direction dir;

	private:
		bool checkInputForAttack(AOEAttack& attack);
		void scoreAttack(AOEAttack& attack);
		bool attackHitSomething_;
	};

} //namespace Game

#endif