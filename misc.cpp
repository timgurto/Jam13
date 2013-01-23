// (C) 2009, 2010 Tim Gurto

#include <cassert>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <queue>
#include "util.h"
#include "globals.h"
#include "misc.h"
#include "Point.h"
#include "Debug.h"
#include "Screen.h"

extern Debug debug;

//Adds a leading space if x < 100 (fps display)
std::string format3(double x){
   std::ostringstream oss;
   if (x < 100)
      oss << ' ';
   oss << x;
   return oss.str();
}

//Adds a leading zero if x < 10 (game file names)
std::string format2(int x){
   std::ostringstream oss;
   if (x < 10)
      oss << '0';
   oss << x;
   debug (oss.str());
   return oss.str();
}

//push a mouse-move event onto the queue, to refresh the
//calculations handled there
void pushMouseMove(){
   SDL_Event fakeMouseMove;
   fakeMouseMove.type = SDL_MOUSEMOTION;
   fakeMouseMove.motion.x = Screen::mousePos.x;
   fakeMouseMove.motion.y = Screen::mousePos.y;
   SDL_PushEvent(&fakeMouseMove);
}

//double % int, preserves fraction
double modulo(double a, int b){
   if (a < b)
      return a;
   int aInt = int(a);
   return aInt % b + a - aInt;
}