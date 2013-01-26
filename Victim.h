// (C) 2013 Tim Gurto

#ifndef VICTIM_H
#define VICTIM_H

#include "Death.h"
#include "Location.h"

namespace Game {

    //One dead or dying person, mapped to a single Death type
    struct Victim{

        static pixels_t vampY;
        
        const Death *death;
        size_t frame;
        int frameTime;
        bool dead;
        Location loc;

        Victim(const Location &locArg, Death *deathArg);

        void draw(bool aboveVampire, Point offset = Point()) const;

        void update(timer_t timeElapsed);
    };

} //namespace Game

#endif