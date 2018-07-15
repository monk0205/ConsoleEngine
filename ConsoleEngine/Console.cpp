#include "pch.h"
#include "Console.h"

Console::Console()
{
}

Console::~Console()
{
}

Console* Console::CreateBuffer(int Width, int Height)
{
	console_width_ = Width;
	console_height_ = Height;

	CONSOLE_CURSOR_INFO cci;
	COORD size = { Width, Height };
	SMALL_RECT rect_;

	rect_.Left = 0;
	rect_.Right = Width - 1;
	rect_.Top = 0;
	rect_.Bottom = Height - 1;

	cci.dwSize = 1;
	cci.bVisible = FALSE;

	console_handle_ = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(console_handle_, size);
	SetConsoleWindowInfo(console_handle_, TRUE, &rect_);
	SetConsoleCursorInfo(console_handle_, &cci);

	return this;
}

Console* Console::BufferWrite(int x, int y, char* string)
{
	DWORD dw;
	COORD pos_ = { x, y };
	SetConsoleCursorPosition(console_handle_, pos_);
	WriteFile(console_handle_, string, strlen(string), &dw, NULL);

	return this;
}

Console* Console::BufferClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(console_handle_, ' ', console_width_ * console_height_, Coor, &dw);
	return this;
}

Console* Console::SetCursorVisibility(bool is_visible_)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console_handle_, &cursorInfo);
	cursorInfo.bVisible = is_visible_;
	SetConsoleCursorInfo(console_handle_, &cursorInfo);

	return this;
}

Console* Console::TextColor(ColorRGB color)
{
	SetConsoleTextAttribute(console_handle_, FindClosestColor(color));
	return this;
}

int Console::FindClosestColor(ColorRGB color)
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
		int dist = Square(colorR - r[i]) + Square(colorB - b[i]) + Square(colorG - g[i]);
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

HANDLE Console::GetConsoleHandle()
{
	return console_handle_;
}