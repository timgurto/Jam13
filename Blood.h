// (C) 2013 Tim Gurto

#ifndef BLOOD_H
#define BLOOD_H

#include <vector>
#include "Surface.h"
#include "Location.h"

namespace Game {


    struct Blood{

        static std::vector<Surface> *images;

        static const timer_t MAX_LIFESPAN;

        Surface *image;
        Location startLoc, loc;

        timer_t lifespan;

        Blood();

        void update(double delta);

        void draw() const;

    };

} //namespace Game

#endif