// (C) 2013 Tim Gurto

#include "Death.h"
#include "Sound.h"

namespace Game {

    Death::Death(const std::string& imagePath,
		Sound* soundPtr,
		size_t framesArg,
		size_t columnsArg,
		const Point& dimArg,
		const Point& offsetArg):
    image(imagePath, true),
	sound(soundPtr),
    frames(framesArg),
    columns(columnsArg),
    dim(dimArg),
    offset(offsetArg){}

} //namespace Game