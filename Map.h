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

        static const size_t MARGIN_SIZE;

        size_t baseTile;
        std::vector<Surface> tiles;
        std::vector<Surface> obstacleTiles;
        double baseProportion;
        double baseObstacleProportion;
        Point tileSize;
        Point mapSize;
        const Location &offset;
        void draw(const Location &offset) const;
        void randomize();
        SDL_Rect getRect() const;
        int *data;
    };

} //namespace Game

#endif