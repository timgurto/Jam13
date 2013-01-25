// (C) 2013 Tim Gurto

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Entity.h"

namespace Game {

    class Vampire : public Entity{

        virtual SDL_Rect drawRect() const;

        virtual SDL_Rect collisionRect() const;

        virtual Surface *image() const;

        static const double SPEED;

    public:

        Vampire(const Location &loc);

        virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

        void update(double delta);

	};

} //namespace Game

#endif