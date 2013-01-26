// (C) 2013 Tim Gurto

#ifndef DEATH_H
#define DEATH_H

#include "Surface.h"
#include "Point.h"

namespace Game {

    //'Death' class: an animation and corpse-image combo.
    struct Death{
        Surface image;
        size_t frames;
        size_t columns;
        Point dim;
        Point offset;

        Death(std::string imagePath, size_t framesArg, size_t columnsArg, Point dimArg, Point offsetArg);
    };

} //namespace Game

#endif