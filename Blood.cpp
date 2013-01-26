// (C) 2013 Tim Gurto

#include "Blood.h"
#include "util.h"

namespace Game {

    std::vector<Surface> *Blood::images = 0;

    const timer_t Blood::MAX_LIFESPAN = 1000;

    Blood::Blood():
    image(&(*images)[rand() % images->size()]),
    startLoc(rand() % 600 + 100, rand() % 300 + 100),
    loc(startLoc),
    lifespan(0){
    }

    void Blood::update(double delta){
        timer_t elapsedTime = delta * DELTA_MODIFIER;
        lifespan += elapsedTime;
    }

    void Blood::draw() const{
        static const timer_t fadeIn = 100;

        SDL_Rect dstRect;
        dstRect.x = loc.x - (*image)->w/2;
        dstRect.y = loc.y - (*image)->h/2;

        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.w = (*image)->w;
        srcRect.y = 0;
        srcRect.h = (*image)->h;

        if (lifespan <= fadeIn){
            srcRect.h = 1.0 * lifespan / fadeIn * (*image)->h;
        }else if (lifespan >= 500){
            double mod = 1.0 * (lifespan - 500) / 500;
            pixels_t modP = mod * (*image)->h;
            srcRect.h -= modP;
            srcRect.y = modP;
            dstRect.y += modP;
        }

        image->draw(screenBuf, &dstRect, &srcRect);
    }

} //namespace Game