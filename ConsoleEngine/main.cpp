#include "pch.h"
#include "Define.h"
#include "World.h"

int main()
{
	SetConsoleTitleA("Console Project");
	//system("mode con:cols=125 lines=25");

	world.Init();

	while (!world.GetIsEnd()) {
		world.Update();
		world.Clear();
		world.BufferWrite(0, 0, const_cast<char*>("Hello, World~!"));
		world.Render();
		Sleep(33 - world.GetDt() * 10);
	}

	world.Dispose();

	return 0;
}