// (C) 2013 Tim Gurto

#include <cassert>
#include "HealthBar.h"
#include "Screen.h"
#include "util.h"

namespace Game {

	const pixels_t HEIGHT = 20;
	const pixels_t OUTLINE_THICKNESS = 1;
	const double FILLING_SPEED = 0.0001;
	const size_t MAX_HEALTH = 100;

	HealthBar::HealthBar() : Entity(),
		fillPercent_(0.0),
		fillingPercent_(0.0)
	{
		loc_.x = 5;
		loc_.y = 3;
	}

	void HealthBar::setHealth(size_t health) {
		fillPercent_ = min(health / (double)MAX_HEALTH, 1.0);
		assert(fillPercent_ >= 0);
		assert(fillPercent_ <= 1.0);
	}

	// Outline
	SDL_Rect HealthBar::drawRect() const{
        return outlineRect();
    }

	// Current fill
    SDL_Rect HealthBar::collisionRect() const{
		return fillRect();
    }

	pixels_t HealthBar::getMaxWidth() const {
		const Point& screenRes = Screen::getScreenRes();
		const pixels_t size = static_cast<pixels_t>(screenRes.x - (loc_.x * 2) + 0.5);
		return std::max(1, size);
	}

	pixels_t HealthBar::getFillWidth() const {
		assert(fillPercent_ >= 0);
		return static_cast<pixels_t>(fillPercent_ * getMaxWidth());
	}

	pixels_t HealthBar::getFillingWidth() const {
		assert(fillingPercent_ >= 0);
		return static_cast<pixels_t>(fillingPercent_ * getMaxWidth());
	}

	// Outline
	SDL_Rect HealthBar::outlineRect() const{
		const pixels_t width = getMaxWidth() + (OUTLINE_THICKNESS * 2);
		const pixels_t height = HEIGHT + (OUTLINE_THICKNESS * 2);
        return makeRect(0, 0, width, height);
    }

	// Current fill
    SDL_Rect HealthBar::fillRect() const{
		const pixels_t width = getFillWidth();
		const pixels_t height = HEIGHT;
        return makeRect(0, 0, width, height);
    }

	// Fill being added/subtracted
    SDL_Rect HealthBar::fillingRect() const{
		const pixels_t width = getFillingWidth();
		const pixels_t height = HEIGHT;
        return makeRect(0, 0, width, height);
    }

    Surface *HealthBar::image() const{
        return 0;
    }

	void HealthBar::update(double delta) {
		const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER);
		fillingPercent_ = max(0.0, fillingPercent_ - (timeElapsed * FILLING_SPEED));
	}

	void HealthBar::draw(Point offset, Surface &surface) const {

		// Outline square
		{
			const SDL_Color outlineColour = GRAY;
			SDL_Rect rect = outlineRect();
			rect.x += static_cast<Sint16>(loc_.x - OUTLINE_THICKNESS + 0.5);
			rect.y += static_cast<Sint16>(loc_.y - OUTLINE_THICKNESS + 0.5);
			surface.box(outlineColour, &rect, OUTLINE_THICKNESS);
		}

		// Fill square
		{
			const SDL_Color fillColour = RED;
			SDL_Rect rect = fillRect();
			rect.x += static_cast<Sint16>(loc_.x + 0.5);
			rect.y += static_cast<Sint16>(loc_.y + 0.5);
			surface.fill(fillColour, &rect);
		}

		// Filling square
		if (fillPercent_ > 0)
		{
			const SDL_Color fillingColour = YELLOW;
			SDL_Rect rect = fillingRect();
			rect.x += static_cast<Sint16>(loc_.x + getFillWidth() + 0.5);
			rect.y += static_cast<Sint16>(loc_.y + 0.5);
			surface.fill(fillingColour, &rect);
		}
		else if (fillPercent_ < 0)
		{
			const SDL_Color fillingColour = BLUE;
			SDL_Rect rect = fillingRect();
			rect.x += static_cast<Sint16>(loc_.x + getFillWidth() + 0.5);
			rect.y += static_cast<Sint16>(loc_.y + 0.5);
			surface.fill(fillingColour, &rect);
		}
	}

} //namespace Game
