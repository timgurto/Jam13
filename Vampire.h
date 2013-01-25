// (C) 2013 Tim Gurto

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Entity.h"

namespace Game {

    class Vampire : public Entity{

        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

    public:

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

	};

} //namespace Game

#endif