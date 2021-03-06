// (C) 2013 Tim Gurto

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Entity.h"
#include "SmallAttack.h"
#include "BatAttack.h"

namespace Game {

	class Person;
    struct GameState;

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
            *attackingH,
            *burningL,
            *burningR;

        const static size_t
            idleColumns,
            idleFrames,
            movingColumns,
            movingFrames,
            attackingColumns,
            attackingFrames,
            burningColumns,
            burningFrames;

        bool visible; //invisibility for post-death

		SmallAttack smallAttack;
		BatAttack batAttack;

		// Time before you can activate the attack again
		// counted from the start of the attack activation
		timer_t cooldownTimer_;

    public:

		// Health of vampire
		double totalBlood_;

        enum VampireState{
            IDLE,
            MOVING,
            ATTACKING,
            BURNING,
            SHOT
        };

        timer_t frameTime; //time until next frame.  Resets at 42ms (~24f/s)
        size_t frame; //current frame

        VampireState state;

        static GameState *gameState;

		static const double MAX_HEALTH;

        Vampire(const Location &loc);

		double getTotalBlood() const;
		double getBloodPercent() const;
		bool isDead() const;
		bool isBloodFull() const;
		void die();

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

        static void setBurningImages(const Surface *l,
                                     const Surface *r);

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		void updateDirection(Direction newDir);

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
	};

} //namespace Game

#endif