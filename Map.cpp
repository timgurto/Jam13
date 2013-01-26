// (C) 2013 Tim Gurto

#include "Map.h"
#include "Location.h"
#include <SDL.h>

namespace Game {

    Map::Map(const Location &offsetArg):
    offset(offsetArg),
    data(0){}

    void Map::draw(const Location &offset) const{
        size_t numTiles = mapSize.x * mapSize.y;
        for (int i = 0; i != numTiles; ++i){
            size_t
                row = i / mapSize.y,
                col = i - (row * mapSize.y);
            SDL_Rect drawRect;
            drawRect.x = row * tileSize.x - offset.x;
            drawRect.y = col * tileSize.y - offset.y;
            tiles[data[i]].draw(screenBuf, &drawRect);
        }
    }

    void Map::randomize(){
        size_t numTiles = mapSize.x * mapSize.y;
        data = (size_t *)realloc(data, sizeof(size_t) * numTiles);
        for (int i = 0; i != numTiles; ++i)
            if (1.0 * rand() / RAND_MAX < baseProportion)
                data[i] = 0;
            else
                data[i] = rand() % (tiles.size()-1) + 1;
    }

    SDL_Rect Map::getRect() const{
        SDL_Rect r;
        r.x = -offset.x;
        r.y = -offset.y;
        r.w = mapSize.x * tileSize.x;
        r.h = mapSize.y * tileSize.y;
        return r;
    }

} //namespace Game