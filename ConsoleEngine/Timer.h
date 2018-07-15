#pragma once
#include "Define.h"

class Timer
{
public:
	Timer();
	~Timer();

	void Reset(int count, float duration, bool autoStart = true);
	void Update(float dt);

	function<void()> onTick;
	function<void()> onFinished;

private:
	bool active_;
	pair<int, int> count_;
	pair<float, float> duration_;
};