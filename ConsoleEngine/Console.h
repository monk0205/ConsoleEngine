#pragma once
#include "Define.h"

class Console
{
public:
	Console();
	~Console();

	Console* createBuffer(int width, int height);
	Console* bufferWrite(int x, int y, char* string);
	Console* bufferClear();

	Console* setCursorVisibility(bool isVisible);
	Console* textColor(ColorRGB color);
	int findClosestColor(ColorRGB color);

	int consoleWidth;
	int consoleHeight;
	int nBufferIndex;

	HANDLE consoleHandle;
};