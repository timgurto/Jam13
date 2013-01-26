// (C) 2013 Tim Gurto

#include "Map.h"
#include "Location.h"
#include <SDL.h>
#include "util.h"
#include "Debug.h"

namespace Game {

    extern Debug debug;

    const size_t Map::MARGIN_SIZE = 10;

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

            const Surface *image;
            if (data[i] >= 0)
                image = &tiles[data[i]];
            else if (data[i] == -1)
                image = &obstacleTiles[0];
            else
                image = &obstacleTiles[1];

            image->draw(screenBuf, &drawRect);
            //if (DEBUG)
            //    if (col == 0 || row == 0 || col == mapSize.x-1 || row == mapSize.y-1)
            //        screenBuf.box(WHITE, &makeRect(drawRect.x+1, drawRect.y+1, tileSize.x-2, tileSize.y-2));
        }
    }

    void Map::randomize(){
        size_t numTiles = mapSize.x * mapSize.y;
        data = (int *)realloc(data, sizeof(int) * numTiles);
        for (int i = 0; i != numTiles; ++i){
            size_t
                row = i / mapSize.y,
                col = i - (row * mapSize.y);
            SDL_Rect drawRect;
            //wall?
            bool
                a = row == MARGIN_SIZE-1 && col >= MARGIN_SIZE-1 && col <= mapSize.x - MARGIN_SIZE,
                b = row == mapSize.y - MARGIN_SIZE && col >= MARGIN_SIZE-1 && col <= mapSize.x - MARGIN_SIZE,
                c = col == MARGIN_SIZE-1 && row >= MARGIN_SIZE-1 && row <= mapSize.x - MARGIN_SIZE,
                d = col == mapSize.x - MARGIN_SIZE && row >= MARGIN_SIZE-1 && row <= mapSize.x - MARGIN_SIZE;

            if (a || b || c || d/* &&
                !lXor(a, b) && !lXor(a, d) && !lXor(c, b) && !lXor(c, d)*/){
                if (1.0 * rand() / RAND_MAX < baseObstacleProportion)
                    data[i] = -1;
                else{
                    data[i] = -2;
                    debug("setting to -2");
                }
            }else{
                if (1.0 * rand() / RAND_MAX < baseProportion)
                    data[i] = 0;
                else
                    data[i] = rand() % (tiles.size()-1) + 1;
            }
        }
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