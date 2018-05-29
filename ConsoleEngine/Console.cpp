#include "pch.h"
#include "Console.h"

Console::Console()
{
}

Console::~Console()
{
}

Console* Console::createBuffer(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;

	CONSOLE_CURSOR_INFO cci;
	COORD size = { width, height };
	SMALL_RECT rect;

	rect.Left = 0;
	rect.Right = width - 1;
	rect.Top = 0;
	rect.Bottom = height - 1;

	cci.dwSize = 1;
	cci.bVisible = FALSE;

	consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(consoleHandle, size);
	SetConsoleWindowInfo(consoleHandle, TRUE, &rect);
	SetConsoleCursorInfo(consoleHandle, &cci);

	return this;
}

Console* Console::bufferWrite(int x, int y, char* string)
{
	DWORD dw;
	COORD pos = { x, y };
	SetConsoleCursorPosition(consoleHandle, pos);
	WriteFile(consoleHandle, string, strlen(string), &dw, NULL);

	return this;
}

Console* Console::bufferClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(consoleHandle, ' ', consoleWidth * consoleHeight, Coor, &dw);
	return this;
}

Console* Console::setCursorVisibility(bool isVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	return this;
}

Console* Console::textColor(ColorRGB textColor, ColorRGB backgroundColor)
{
	SetConsoleTextAttribute(consoleHandle, findClosestColor(backgroundColor) << 4 | findClosestColor(textColor));
	return this;
}

int Console::findClosestColor(ColorRGB color)
{
	int r[] = { 0, 0, 0, 0, 128, 128, 128, 128, 192, 0, 0, 0, 255, 255, 255, 255 };
	int g[] = { 0, 0, 128, 128, 0, 0, 128, 128, 192, 0, 255, 255, 0, 0, 255, 255 };
	int b[] = { 0, 128, 0, 128, 0, 128, 0, 128, 192, 255, 0, 255, 0, 255, 0, 255 };

	int colorR = color.red & 0xff;
	int colorG = color.green & 0xff;
	int colorB = color.blue & 0xff;

	int bestIndex = 0;
	int bestDist = INT32_MAX;
	for (int i = 0; i < 16; i++) {
		int dist = square(colorR - r[i]) + square(colorB - b[i]) + square(colorG - g[i]);
		if (dist < bestDist) {
			bestIndex = i;
			bestDist = dist;
		}
	}

	int consoleValue = ((r[bestIndex] > 0) << 2) | ((g[bestIndex] > 0) << 1) | (b[bestIndex] > 0);

	if (bestIndex == 7) // gray
		return FOREGROUND_INTENSITY;
	else if (bestIndex == 8) // lightgray
		return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
	else if (bestIndex > 8)
		return consoleValue | FOREGROUND_INTENSITY;
	return consoleValue;
}