// (C) 2013 Tim Gurto

#include "Victim.h"
#include "Death.h"
#include "util.h"

namespace Game {

    pixels_t Victim::vampY = 0;

    Victim::Victim(const Location &locArg, Death *deathArg):
    loc(locArg),
    death(deathArg),
    frame(0),
    frameTime(42),
    dead(false){}

    void Victim::draw(bool aboveVampire, Point offset) const{
        //if (aboveVampire && (loc.y > vampY)
        if (aboveVampire != (loc.y < vampY))
            return;

        SDL_Rect drawRect;
        drawRect.x = loc.x - death->offset.x - offset.x;
        drawRect.y = loc.y - death->offset.y - offset.y;

        SDL_Rect srcRect;
        size_t
            row = frame / death->columns,
            col = frame % death->columns;
        srcRect.x = col * death->dim.x;
        srcRect.y = row * death->dim.y;
        srcRect.w = death->dim.x;
        srcRect.h = death->dim.y;

        death->image.draw(screenBuf, &drawRect, &srcRect);
    }

    void Victim::update(timer_t timeElapsed){
        if (dead)
            return;

        if (timeElapsed > frameTime){
            ++frame;
            if (frame >= death->frames){
                dead = true;
                --frame;
            }else
                frameTime = max<int>(42 - (timeElapsed - frameTime), 0);
        }else
            frameTime -= timeElapsed;
    }


} //namespace Game
