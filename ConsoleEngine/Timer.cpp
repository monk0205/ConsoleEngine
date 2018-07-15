#include "pch.h"
#include "Timer.h"
#include "World.h"

Timer::Timer() : active_(false)
{
	onTick = []() {};
	onFinished = []() {};

	world.GetTimers().push_back(this);
}

Timer::~Timer()
{
	world.GetTimers().erase(remove(world.GetTimers().begin(), world.GetTimers().end(), this), world.GetTimers().end());
}

void Timer::Reset(int count, float duration, bool AutoStart)
{
	active_ = AutoStart;
	this->count_.first = 0;
	this->count_.second = count;
	this->duration_.first = 0;
	this->duration_.second = duration;
}

void Timer::Update(float dt)
{
	if (active_) {
		duration_.first += dt;
		if (duration_.first >= duration_.second) {
			duration_.first = 0;
			onTick();
			if (++count_.first >= count_.second) {
				onFinished();
				active_ = false;
			}
		}
	}
}