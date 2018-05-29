#include "pch.h"
#include "Timer.h"
#include "World.h"

Timer::Timer() : active(false)
{
	onTick = []() {};
	onFinished = []() {};

	world.timers.push_back(this);
}

Timer::~Timer()
{
	//world.getTimers().erase(this);
}

void Timer::reset(int count, float duration, bool AutoStart)
{
	active = AutoStart;
	this->count.first = 0;
	this->count.second = count;
	this->duration.first = 0;
	this->duration.second = duration;
}

void Timer::update(float dt)
{
	if (active) {
		duration.first += dt;
		if (duration.first >= duration.second) {
			duration.first = 0;
			onTick();
			if (++count.first >= count.second) {
				onFinished();
				active = false;
			}
		}
	}
}