#pragma once
#include "Define.h"

class Timer
{
public:
	Timer();
	~Timer();

	void reset(int count, float duration, bool autoStart = true);
	void update(float dt);

	function<void()> onTick;
	function<void()> onFinished;

	bool active;
	pair<int, int> count;
	pair<float, float> duration;
};