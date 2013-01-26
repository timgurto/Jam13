// (C) 2013 Tim Gurto

#ifndef MAP_H
#define MAP_H

#include "Surface.h"
#include "Location.h"

#include <SDL.h>
#include <vector>

namespace Game {

    struct Map{

        Map(const Location &offsetArg); 

        size_t baseTile;
        std::vector<Surface> tiles;
        double baseProportion;
        Point tileSize;
        Point mapSize;
        const Location &offset;
        void draw() const;
        void randomize();
        SDL_Rect getRect() const;
        size_t *data;
    };

} //namespace Game

#endif