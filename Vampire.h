// (C) 2013 Tim Gurto

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Entity.h"
#include "AOEAttack.h"

namespace Game {

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
        };

        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

        static const double SPEED;

        static const Surface
            *idleE,
            *idleF,
            *idleG,
            *idleH;

        const static size_t
            idleColumns,
            idleFrames,
            walkingColumns,
            walkingFrames;

        timer_t frameTime; //time until next frame.  Resets at 42ms (~24f/s)
        size_t frame; //current frame

        VampireState state;

    public:

		AOEAttack aoeAttack;

        Vampire(const Location &loc);

        SDL_Rect getDrawRect(Point offset) const;

        SDL_Rect getCollisionRect(Point offset) const;

        static void setIdleImages(const Surface *e,
                                  const Surface *f,
                                  const Surface *g,
                                  const Surface *h);

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

        void update(double delta);

        Direction lastUpDown;
        Direction lastLeftRight;
        Direction dir;
        void updateDirection(Direction newDir);

	};

} //namespace Game

#endif