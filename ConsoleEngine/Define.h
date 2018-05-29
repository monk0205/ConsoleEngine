#pragma once
#include "pch.h"

struct Vec2
{
	float x, y;

	Vec2() : x(0), y(0) {

	}

	Vec2(int x, int y) : x(x), y(y) {
		
	}

	Vec2(float x, float y) : x(x), y(y) {
		
	}

	Vec2 add(Vec2 v) {
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	Vec2 sub(Vec2 v) {
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}

	Vec2 vecToInt() {
		Vec2 v(ceil(this->x), ceil(this->y));
		return v;
	}
};

struct ColorRGB
{
	int red, green, blue;

	ColorRGB() : red(0), green(0), blue(0) {

	}

	ColorRGB(int red, int green, int blue) : red(red), green(green), blue(blue) {

	}
};

class Rect :
	public RECT
{
public:
	Rect() {
		this->left = 0;
		this->top = 0;
		this->right = 0;
		this->bottom = 0;
	}

	Rect(int left, int top, int right, int bottom) {
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	bool intersectsRect(Rect rect) {
		Rect tmpRect;
		return IntersectRect(&tmpRect, this, &rect);
	}

	bool intersectsRect(Rect rect, Vec2 pos) {
		Rect tmpRect;
		return IntersectRect(&tmpRect, this, &rect.offset(pos));
	}

	Rect offset(Vec2 pos) {
		Rect r = *this;
		r.left += pos.x;
		r.top += pos.y;
		r.right += pos.x;
		r.bottom += pos.y;
		return r;
	}

	int width() {
		return right - left;
	}

	int height() {
		return bottom - top;
	}

	Vec2 center() {
		return Vec2(width() / 2, height() / 2);
	}
};

inline int random(int to, int from)
{
	return (rand() % (from - to + 1)) + to;
}

inline int square(int x) { return x * x; }