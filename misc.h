// (C) 2009, 2010 Tim Gurto

#ifndef MISC_H
#define MISC_H

#include <fstream>
#include <string>
#include <queue>
#include <SDL.h>

#include "types.h"
#include "globals.h"

//double % int, preserves fraction
double modulo(double a, int b);

//Adds a leading space if x < 100
std::string format3(double x);

//Adds a leading zero if x < 10
std::string format2(int x);

//empties a std::queue
template<typename T>
void emptyQueue(std::queue<T> &q){
   while (!q.empty())
      q.pop();
}

//push a mouse-move event onto the queue, to refresh the
//calculations handled there
void pushMouseMove();

#endif