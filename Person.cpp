// (C) 2013 Tim Gurto

#include "Person.h"
#include "util.h"

namespace Game {

	Person::Person(Point startPos) : Entity() {
		loc_ = startPos;
	}

    SDL_Rect Person::drawRect() const{
        return makeRect(-3, -3, 6, 6);
    }

    SDL_Rect Person::collisionRect() const{
        return makeRect(-3, -3, 6, 6);
    }

    Surface *Person::image() const{
        return 0;
    }

    void Person::draw(Point offset, Surface &surface) const{
        SDL_Rect rect = drawRect();
        surface.fill(BLUE,
			&makeRect(loc_.x-rect.x-offset.x,
				loc_.y-rect.y-offset.y,
				rect.w,
				rect.h));
    }

} //namespace Game