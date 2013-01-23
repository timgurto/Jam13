// (C) 2011 Tim Gurto

#ifndef LOCATION_H
#define LOCATION_H

#include "Point.h"
#include "SDL.h"

struct Location{
   double x;
   double y;

   Location(const Point &rhs);
   Location(double x = 0, double y = 0);
   
   operator Point() const;

   operator SDL_Rect() const;
};

#endif