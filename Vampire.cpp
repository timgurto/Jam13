// (C) 2013 Tim Gurto

#include "Vampire.h"
#include "util.h"

namespace Game {

    SDL_Rect Vampire::drawRect() const{
        return makeRect(-10, -10, 20, 20);
    }

    SDL_Rect Vampire::collisionRect() const{
        return makeRect(-10, -10, 20, 20);
    }

    Surface *Vampire::image() const{
        return 0;
    }

    void Vampire::draw(Point offset, Surface &surface) const{
        SDL_Rect rect = drawRect();
        surface.fill(RED, &makeRect(loc_.x-rect.x-offset.x, loc_.y-rect.y-offset.y, rect.w, rect.h));
    }

} //namespace Game