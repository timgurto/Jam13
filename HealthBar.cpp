// (C) 2013 Tim Gurto

#include <cassert>
#include <cmath>
#include "Debug.h"
#include "HealthBar.h"
#include "Screen.h"
#include "util.h"

namespace Game {

	extern Debug debug;
	const pixels_t OUTLINE_THICKNESS = 1;

	HealthBar::HealthBar(double startingPercent) : Entity(),
		MAX_HEALTH(100),
		fillPercent_(startingPercent),
		fillingPercent_(0.0),
		timeToHighlightHealthJump_(0)
	{
		loc_.x = 5;
		loc_.y = 3;
	}

	pixels_t HealthBar::getHeight() const {
		return fullBar.getDim().y;
	}

	double HealthBar::getPercent() const {
		return fillPercent_ + fillingPercent_;
	}

	// Set health
	// Health bar is animated with changes
	void HealthBar::setPercent(double p) {

		// Get difference between bar's current health and desired health
		const double diff = p - getPercent();

		// No change - return
		if (fabs(diff) < 0.00001) {
			return;
		}
		timeToHighlightHealthJump_ = 1000;

		// Calculate amount we are filling
		fillingPercent_ = fillingPercent_ + max(-1.0, min(diff, 1.0));
		assert(fillingPercent_ <= 1.0);
		assert(fillingPercent_ >= -1.0);
	}

	void HealthBar::setRawPercent(double p) {
		fillPercent_ = p;
		fillPercent_ = max(0.0, min(fillPercent_, 1.0));
		fillingPercent_ = 0.0;
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
		assert(fillingPercent_ >= -1.0);
		assert(fillingPercent_ <= 1.0);
		const double diff = fillingPercent_ * getMaxWidth();
		return static_cast<pixels_t>(fabs(diff) + 0.5);
	}

	// Outline
	SDL_Rect HealthBar::outlineRect() const{
		const pixels_t width = getMaxWidth() + (OUTLINE_THICKNESS * 2);
		const pixels_t height = getHeight() + (OUTLINE_THICKNESS);
        return makeRect(0, 0, width, getHeight());
    }

	// Current fill
    SDL_Rect HealthBar::fillRect() const{
		const pixels_t width = getFillWidth();
		const pixels_t height = getHeight();
        return makeRect(0, 0, width, getHeight());
    }

	// Fill being added/subtracted
    SDL_Rect HealthBar::fillingRect() const{
		const pixels_t width = getFillingWidth();
		const pixels_t height = getHeight();
        return makeRect(0, 0, width, getHeight());
    }

    Surface *HealthBar::image() const{
        return 0;
    }

	void HealthBar::update(double delta) {

		const timer_t timeElapsed = static_cast<timer_t>(delta * DELTA_MODIFIER + 0.5);

		// Pause bar for 1s before moving
		if (timeToHighlightHealthJump_ > 0) {

			// Prevent underflow
			if (timeToHighlightHealthJump_ < timeElapsed) {
				// Clamp to 0
				timeToHighlightHealthJump_ = 0;
			}
			else {
				// Subtract time
				timeToHighlightHealthJump_ -= timeElapsed;
			}
		}

		// Use std for double
		else if (fabs(fillingPercent_) > 0.0) {

			const double FILLING_SPEED = pow(3, 1.0-fillingPercent_) * 0.005;
			//debug("FILLING_SPEED ", FILLING_SPEED);

			double fillDelta = fillingPercent_ * timeElapsed * FILLING_SPEED;
			//debug("fillDelta1 ", fillDelta);
			if ((fillPercent_ + fillDelta) > 1.0) {
				fillDelta = fillingPercent_;
			}
			else if ((fillPercent_ + fillDelta) < 0.0) {
				fillDelta = fillingPercent_;
			}
			//debug("fillDelta2 ", fillDelta);

			fillPercent_ += fillDelta;
			assert(fillPercent_ >= 0.0);
			assert(fillPercent_ <= 1.0);

			fillingPercent_ -= fillDelta;
			assert(fillingPercent_ >= -1.0);
			assert(fillingPercent_ <= 1.0);
		}
	}

	void HealthBar::draw(Point offset, Surface &surface) const {

		// Fill square
		{
			SDL_Rect rect = fillRect();
			rect.x += static_cast<Sint16>(loc_.x + 0.5);
			rect.y += static_cast<Sint16>(loc_.y + 0.5);
			fullBar.draw(surface, &rect, &rect);
		}

		// Filling square
		if (fillingPercent_ > 0)
		{
			SDL_Rect rect = fillingRect();
			rect.x += static_cast<Sint16>(loc_.x + getFillWidth() + 0.5);
			rect.y += static_cast<Sint16>(loc_.y + 0.5);
			positiveFillingBar.draw(surface, &rect, &rect);
		}
		else if (fillingPercent_ < 0)
		{
			SDL_Rect rect = fillingRect();
			rect.x += static_cast<Sint16>(loc_.x + getFillWidth() - getFillingWidth() + 0.5);
			rect.y += static_cast<Sint16>(loc_.y + 0.5);
			negativeFillingBar.draw(surface, &rect, &rect);
		}

		// Outline square
		{
			const SDL_Color outlineColour = GRAY;
			SDL_Rect rect = outlineRect();
			rect.x += static_cast<Sint16>(loc_.x - OUTLINE_THICKNESS + 0.5);
			rect.y += static_cast<Sint16>(loc_.y - OUTLINE_THICKNESS + 0.5);
			outlineBar.draw(surface, &rect, &rect);
		}
	}

} //namespace Game
