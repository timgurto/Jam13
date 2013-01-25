// (C) 2013 Tim Gurto

#ifndef VAMPIRE_H
#define VAMPIRE_H

#include "Entity.h"

namespace Game {

    class Vampire : public Entity{
    virtual SDL_Rect drawRect() const = 0; //returns the hardcoded draw rectangle; x and y are an offset
    virtual SDL_Rect collisionRect() const = 0; //returns the hardcoded collision rectangle; x and y are an offset
    virtual Surface *image() const = 0;
	};

} //namespace Game

#endif