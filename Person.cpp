// (C) 2013 Tim Gurto

#include "Person.h"
#include "util.h"

namespace Game {

    const timer_t Person::MAX_AMBLE_TIMER = 4000;
    const double Person::AMBLE_CHANCE = 0.3;
    const double Person::SPEED = 1;

	Person::Person(Point startPos) :
    Entity(),
    ambling_(1.0*rand()/RAND_MAX < AMBLE_CHANCE),
    ambleTimer_(rand()%MAX_AMBLE_TIMER),
    direction_(rand()%4){
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
        SDL_Color color = ambling_ ? WHITE : BLUE;
        surface.fill(color,
			&makeRect(loc_.x-rect.x-offset.x,
				loc_.y-rect.y-offset.y,
				rect.w,
				rect.h));
    }

    void Person::update(double delta){

        //ambling timer
        timer_t timeElapsed = delta * DELTA_MODIFIER;
        if (ambleTimer_ <= timeElapsed){
            ambleTimer_ = rand() % MAX_AMBLE_TIMER;
            ambling_ = 1.0*rand()/RAND_MAX < AMBLE_CHANCE;
            direction_ = rand() % 4;
        }else{
            ambleTimer_ -= timeElapsed;
        }

        //ambling
        if (ambling_){
            double distance = SPEED * delta;
            switch (direction_){
            case 0:
                loc_.x -= distance;
                break;
            case 1:
                loc_.x += distance;
                break;
            case 2:
                loc_.y -= distance;
                break;
            case 3:
                loc_.y += distance;
            }
        }


    }

} //namespace Game