// (C) 2013 Tim Gurto

#ifndef PERSON_H
#define PERSON_H

#include "Entity.h"
#include "Heart.h"

namespace Game {

    class Person : public Entity{


        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

		Heart heart;

        timer_t ambleTimer_;
        bool ambling_;
        static const timer_t MAX_AMBLE_TIMER;
        static const double AMBLE_CHANCE;
        static const double SPEED;
        int direction_;

    public:

		Person(Point startPos, Mix_Chunk* beat);

		virtual void update(double delta, pixels_t distToVamp);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

	};

} //namespace Game

#endif