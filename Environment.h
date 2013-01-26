// (C) 2013 Tim Gurto

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "types.h"

namespace Game {

    class Environment{

		// Time until game ends
		timer_t countdownTimer_;

    public:
		static const timer_t COUNTDOWN_TIME;

		Environment();

		void Environment::update(double delta);

		bool isSunUp() const;
	};

} //namespace Game

#endif