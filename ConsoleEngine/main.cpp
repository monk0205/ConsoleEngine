#include "pch.h"
#include "Define.h"
#include "World.h"

int main()
{
	SetConsoleTitleA("Console Project");

	world.init();

	while (!world.isEnd) {
		world.update();
		world.clear();
		world.bufferWrite(0, 0, const_cast<char*>("Hello, World~!"));
		world.render();
		Sleep(33 - world.dt * 10);
	}

	world.dispose();

	return 0;
}