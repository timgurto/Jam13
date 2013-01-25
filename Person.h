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
    public:

		Person(Point startPos, Mix_Music* beat);

		virtual void update(double delta);
        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

	};

} //namespace Game

#endif