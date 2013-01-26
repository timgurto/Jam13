// (C) 2013 Tim Gurto

#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "Entity.h"
#include "Surface.h"

namespace Game {

	class HealthBar : public Entity{
	public:

		HealthBar(double startingHealth, double maxHealth);

		pixels_t getHeight() const;

		virtual SDL_Rect drawRect() const;
        virtual SDL_Rect collisionRect() const;

		virtual SDL_Rect outlineRect() const;
        virtual SDL_Rect fillRect() const;
		virtual SDL_Rect fillingRect() const;

        virtual Surface *image() const;

		double getHealth() const;
		void setHealth(double health);

		void update(double delta);
		virtual void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		Surface negativeFillingBar;
		Surface outlineBar;
		Surface fullBar;
		Surface positiveFillingBar;

	private:
		const double MAX_HEALTH;
		double fillPercent_;
		double fillingPercent_;

		pixels_t getMaxWidth() const;
		pixels_t getFillWidth() const;
		pixels_t getFillingWidth() const;
	};

} //namespace Game

#endif