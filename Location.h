// (C) 2011 Tim Gurto

#ifndef LOCATION_H
#define LOCATION_H

#include "Point.h"
#include "SDL.h"

namespace Game {

struct Location{
   double x;
   double y;

   Location(const Point &rhs);
   Location(double x = 0, double y = 0);

   Location operator-(const Location &rhs) const;
   
   operator Point() const;

   operator SDL_Rect() const;
};

} // namespace Game

#endif