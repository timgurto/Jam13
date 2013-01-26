// (C) 2013 Tim Gurto

#include "Death.h"

namespace Game {

    Death::Death(std::string imagePath, size_t framesArg, size_t columnsArg, Point dimArg, Point offsetArg):
    image(imagePath, true),
    frames(framesArg),
    columns(columnsArg),
    dim(dimArg),
    offset(offsetArg){}

} //namespace Game