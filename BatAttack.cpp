// (C) 2013 Tim Gurto

#include "BatAttack.h"
#include "Point.h"
#include "Debug.h"
#include "util.h"

namespace Game {

extern Debug debug;

    const size_t BatAttack::FRAMES = 20;

    const size_t BatAttack::COLUMNS = 5;

    const Point BatAttack::DIM(384, 384);

    BatAttack::BatAttack():
    image(IMAGE_PATH + "Vampire/batAttack.png", true),
    frame(0),
    frameTime(0){}

	timer_t BatAttack::getAttackingTime() const {
		return 2000;
	}

	timer_t BatAttack::getCooldownTime() const {
		return 2000;
	}

	pixels_t BatAttack::getRadius() const {
		return 200;
	}

	SDLKey BatAttack::getKey() const {
		return SDLK_x;
	}

    void BatAttack::draw(Point offset, Surface &surface) const{
        if (!attacking_)
            return;

        SDL_Rect drawRect;
        drawRect.x = loc_.x - DIM.x/2 - offset.x;
        drawRect.y = loc_.y - DIM.y/2 - offset.y;
        
        size_t
            row = frame / COLUMNS,
            col = frame % COLUMNS;
        SDL_Rect srcRect;
        srcRect.x = col * DIM.x;
        srcRect.y = row * DIM.y;
        srcRect.w = DIM.x;
        srcRect.h = DIM.y;

        image.draw(screenBuf, &drawRect, &srcRect);
    }

    void BatAttack::update(double delta){
        AOEAttack::update(delta);

        if (attacking_){
            //update frame
            timer_t timeElapsed = delta * DELTA_MODIFIER;
debug(frameTime);
            if (timeElapsed > frameTime){
                ++frame;
                if (frame >= FRAMES)
                    frame = 0;
                frameTime = max<int>(42 - (timeElapsed - frameTime), 0);
            }else
                frameTime -= timeElapsed;
        }
    }

    bool BatAttack::isBatAttack(){
       return true;
    }

	int BatAttack::getFailureCost() const {
		return -3;
	}

	int BatAttack::getSuccessBonus() const {
		return 1;
	}

} //namespace Game