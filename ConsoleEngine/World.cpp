#include "pch.h"
#include "World.h"
#include "Scene.h"
#include "TestScene.h"

World::World() : currentScene(nullptr), isEnd(false), nConsoleIndex(0)
{

}

World::~World()
{

}

void World::init()
{
	srand((unsigned)time(NULL));
	changeScene(new TestScene());
	ZeroMemory(currentKeys, sizeof(currentKeys));
	ZeroMemory(lastKeys, sizeof(lastKeys));
	currentClock = clock();
	lastClock = clock();

	createBuffer(1280, 720);
}

void World::dispose()
{
	if (currentScene) {
		delete currentScene;
	}

	for (int i = 0; i < 2; i++) {
		CloseHandle(console[i].consoleHandle);
	}
}

void World::update()
{
	lastClock = currentClock;
	currentClock = clock();
	dt = (double)(currentClock - lastClock) / CLOCKS_PER_SEC;

	for (int i = 0; i < 256; i++) {
		lastKeys[i] = currentKeys[i];
		currentKeys[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mousePos);
	ScreenToClient(GetConsoleWindow(), &mousePos);

	if (currentScene)
		currentScene->update(dt);

	for (auto* timer : timers)
		timer->update(dt);

	if (getKeyState(VK_ESCAPE) > 0) {
		isEnd = true;
	}
}

void World::render()
{
	if (currentScene)
		currentScene->render();

	flipping();
}

void World::clear()
{
	console[nConsoleIndex].bufferClear();
}

void World::changeScene(Scene* scene)
{
	if (currentScene) {
		delete currentScene;
	}

	currentScene = scene;
}

int World::getKeyState(int vk)
{
	if (currentKeys[vk] && lastKeys[vk]) return 2;
	if (currentKeys[vk] && !lastKeys[vk]) return 1;
	if (!currentKeys[vk] && lastKeys[vk]) return -1;
	return -2;
}

Vec2 World::getMousePos()
{
	return Vec2(mousePos.x / 12, mousePos.y / 24);
}

Vec2 World::getMousePosToScene()
{
	return getMousePos().sub(this->currentScene->pos).vecToInt();
}

void World::createBuffer(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;
	console[0].createBuffer(width, height);
	console[1].createBuffer(width, height);
}

void World::bufferSetColor(ColorRGB textColor, ColorRGB backgroundColor)
{
	console[nConsoleIndex].textColor(textColor, backgroundColor);
}

void World::bufferWrite(int x, int y, char* string)
{
	console[nConsoleIndex].bufferWrite(x, y, string);
}

void World::flipping()
{
	//Sleep(33);
	SetConsoleActiveScreenBuffer(console[nConsoleIndex].consoleHandle);
	nConsoleIndex = !nConsoleIndex;
}

World world;