// (C) 2011 Tim Gurto

#include "Location.h"
#include "Point.h"

Location::Location(const Point &rhs):
x(rhs.x),
y(rhs.y){}

Location::Location(double x, double y):
x(x),
y(y){}

Location::operator Point() const{
   return Point(pixels_t(x+.5), pixels_t(y+.5));
}

Location::operator SDL_Rect() const{
   SDL_Rect r;
   r.x = Sint16(x+.5);
   r.y = Sint16(y+.5);
   r.w = r.h = 0;
   return r;
}