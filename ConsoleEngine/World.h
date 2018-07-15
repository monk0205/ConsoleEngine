#pragma once
#include "Define.h"
#include "Console.h"

class Scene;
class Timer;

class World
{
public:
	World();
	~World();

	void Init();
	void Dispose();

	void Update();
	void Render();
	void Clear();

	void ChangeScene(Scene* scene);
	int GetKeyState(int vk);
	Vec2 GetMousePos();
	Vec2 GetMousePosToScene();

	void CreateBuffer(int Width, int Height);
	void BufferSetColor(ColorRGB color);
	void BufferWrite(int x, int y, char* string);
	void Flipping();

	bool GetIsEnd();
	float GetDt();
	vector<Timer*> GetTimers();
	int GetConsoleWidth();
	int GetConsoleHeight();

private:
	bool is_end_;
	POINT mouse_pos_;
	Scene* current_scene_;

	bool current_keys_[256];
	bool last_keys_[256];

	clock_t current_clock_;
	clock_t last_clock_;
	float dt_;

	vector<Timer*> timers_;

	int n_console_index_;
	Console console_[2];
	int console_width_;
	int console_height_;
};

extern World world;