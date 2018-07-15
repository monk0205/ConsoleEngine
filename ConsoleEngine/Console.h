#pragma once
#include "Define.h"

class Console
{
public:
	Console();
	~Console();

	Console* CreateBuffer(int Width, int Height);
	Console* BufferWrite(int x, int y, char* string);
	Console* BufferClear();

	Console* SetCursorVisibility(bool is_visible_);
	Console* TextColor(ColorRGB color);
	int FindClosestColor(ColorRGB color);

	HANDLE GetConsoleHandle();

private:
	int console_width_;
	int console_height_;

	HANDLE console_handle_;
};