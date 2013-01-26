// (C) 2013 Tim Gurto

#ifndef DEATH_H
#define DEATH_H

#include "Surface.h"
#include "Point.h"

namespace Game {

	class Sound;

    //'Death' class: an animation and corpse-image combo.
    struct Death{
        Surface image;
		Sound* sound;
        size_t frames;
        size_t columns;
        Point dim;
        Point offset;

        Death(const std::string& imagePath,
			Sound* soundPtr,
			size_t framesArg,
			size_t columnsArg,
			const Point& dimArg,
			const Point& offsetArg);
    };

} //namespace Game

#endif