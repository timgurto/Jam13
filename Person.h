// (C) 2013 Tim Gurto

#ifndef PERSON_H
#define PERSON_H

#include "Entity.h"
#include "Sound.h"

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
        timer_t heartTimer_; //time remaining until next beat
        static const pixels_t MAX_SOUND_DISTANCE;
        //double stress_; //maybe bool would be better.  Determines heartrate.

		// Life
		static const int MAX_LIFE;
		int life_;

    public:
        static Sound *heartbeat;
        static const int MAX_HEARTBEATS;
        bool isClosest; //whether this person is (one of) the closest to the vampire

		Person(Point startPos);

		virtual void update(double delta, pixels_t distToVamp);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		// Get's hit - remove life
		void hit(int hitLife);
		bool isDead() const;
	};

} //namespace Game

#endif