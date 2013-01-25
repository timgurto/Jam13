// (C) 2013 Tim Gurto

#ifndef PERSON_H
#define PERSON_H

#include "Entity.h"

namespace Game {

    class Person : public Entity{


        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

    public:

		Person(Point startPos);

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

	};

} //namespace Game

#endif