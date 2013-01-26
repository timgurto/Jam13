// (C) 2013 Tim Gurto

#ifndef PERSON_H
#define PERSON_H

#include "Entity.h"
#include "Sound.h"
#include "GameState.h"

namespace Game {

    class Person : public Entity{

        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

        //ambling
        timer_t ambleTimer_;
        bool ambling_;
        static const timer_t MAX_AMBLE_TIMER;
        static const double AMBLE_CHANCE;
        static const double SPEED;
        int direction_;

        //heartbeat
        static const pixels_t MAX_SOUND_DISTANCE;

		// Life
		int life_;

    public:
		static const int MAX_LIFE;

        static GameState *state;

		Person(Point startPos);

		virtual void update(double delta, pixels_t distToVamp);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		// Gets hit: remove life
		void hit(int hitLife, bool isBatAttack);
		bool isDead() const;
	};

} //namespace Game

#endif