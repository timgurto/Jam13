// (C) 2013 Tim Gurto

#include "Vampire.h"
#include "util.h"

namespace Game {

    const double Vampire::SPEED = 3;

    Vampire::Vampire(const Location &loc){    
        loc_ = loc;
    }

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

		aoeAttack.draw(offset, surface);

        SDL_Rect rect = drawRect();
        surface.fill(RED, &makeRect(loc_.x-rect.x-offset.x, loc_.y-rect.y-offset.y, rect.w, rect.h));
		
		Entity::draw(offset, surface);
	}

    void Vampire::update(double delta){
        //movement through arrow keys
        bool
            up =    isKeyPressed(SDLK_UP),
            down =  isKeyPressed(SDLK_DOWN),
            left =  isKeyPressed(SDLK_LEFT),
            right = isKeyPressed(SDLK_RIGHT);

        if (up && down)
            up = down = false;
        if (left && right)
            left = right = false;

        double distance = delta * SPEED;
        if ((up || down) && (left || right))
            //diagonal movement
            distance *= INV_SQRT2; //for each of the two directions

        if (up)
            loc_.y -= distance;
        if (down)
            loc_.y += distance;
        if (left)
            loc_.x -= distance;
        if (right)
            loc_.x += distance;

		// Killing
		if (isKeyPressed(SDLK_SPACE)) {
			aoeAttack.activate(loc_);
		}
		else {
			aoeAttack.deactivate();
		}
    }

} //namespace Game