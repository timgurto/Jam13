// (C) 2013 Tim Gurto

#ifndef ENTITY_H
#define ENTITY_H

#include "Surface.h"
#include "SDL.h"
#include "Location.h"
#include "Point.h"

namespace Game {
   
   //Inheritable class for in-game objects which have a separate collision box and draw-rectangle.
   class Entity{

      Location loc_;

      virtual SDL_Rect drawRect() const = 0; //returns the hardcoded draw rectangle; x and y are an offset
      virtual SDL_Rect collisionRect() const = 0; //returns the hardcoded collision rectangle; x and y are an offset
      virtual Surface *image() const = 0;

   public:

      //The collision box for this object
      SDL_Rect getCollisionBox() const;

      const Location &getLoc() const;

      bool collidesWithEntity(const Entity &rhs) const;
      bool collidesWithPoint(const Point &rhs) const;

      virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

      //comparison, for sorting/sets/maps.  Compares y co-ordinate of location.
      friend bool lessThan(const Entity &lhs, const Entity &rhs);

   };

} //namespace Game

#endif