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

	void init();
	void dispose();

	void update();
	void render();
	void clear();

	void changeScene(Scene* scene);
	int getKeyState(int vk);
	Vec2 getMousePos();
	Vec2 getMousePosToScene();

	void createBuffer(int width, int height);
	void bufferSetColor(ColorRGB textColor, ColorRGB backgroundColor);
	void bufferWrite(int x, int y, char* string);
	void flipping();

	bool isEnd;
	POINT mousePos;
	Scene* currentScene;

	bool currentKeys[256];
	bool lastKeys[256];

	clock_t currentClock;
	clock_t lastClock;
	float dt;

	vector<Timer*> timers;

	int nConsoleIndex;
	Console console[2];
	int consoleWidth;
	int consoleHeight;
};

extern World world;