// (C) 2013 Tim Gurto

#include "Person.h"
#include "util.h"

namespace Game {

	Person::Person(Point startPos, Mix_Chunk* beat) :
		Entity(),
		heart(beat) {
		loc_ = startPos;
	}

    SDL_Rect Person::drawRect() const{
        return makeRect(-5, -5, 5, 5);
    }

    SDL_Rect Person::collisionRect() const{
        return makeRect(-5, -5, 5, 5);
    }

    Surface *Person::image() const{
        return 0;
    }

	void Person::update(double delta) {
		heart.update(delta);
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