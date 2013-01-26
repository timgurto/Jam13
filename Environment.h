// (C) 2013 Tim Gurto

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "types.h"
#include "HealthBar.h"

namespace Game {

    class Environment{

		// Time until game ends
		timer_t countdownTimer_;
		

    public:
		static const timer_t COUNTDOWN_TIME;

		Environment(double startingHealth);

		void update(double delta);
		void draw(Point offset = Point(), Surface &surface = screenBuf) const;

		bool isSunUp() const;

		HealthBar healthBar_;
	};

} //namespace Game

#endif