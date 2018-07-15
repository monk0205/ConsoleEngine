#include "pch.h"
#include "Sprite.h"
#include "World.h"
#include "Scene.h"

Sprite::Sprite() : color_(255, 255, 255)
{
}

Sprite::Sprite(string data) : color_(255, 255, 255)
{
	SetStr(data);
}

Sprite::~Sprite()
{
}

Sprite& Sprite::SetStr(string str)
{
	data_.clear();
	data_.push_back(str);
	Rect rect = GetRect();
	rect.right = str.length();
	rect.bottom = 1;
	SetRect(rect);
	return *this;
}

Sprite& Sprite::AddStr(string str)
{
	data_.push_back(str);
	Rect rect = GetRect();
	rect.right = max(rect.right, str.length());
	rect.bottom++;
	SetRect(rect);
	return *this;
}

void Sprite::Render()
{
	if (!GetIsVisible() || data_.empty()) 
		return;

	Entity::Render();

	Vec2 p = GetPos();
	if (GetParent()) {
		p.x += GetParent()->GetPos().x;
		p.y += GetParent()->GetPos().y;
	}

	world.BufferSetColor(color_);

	int y = 0;
	for (string str : data_) {
		for (int x = 0; x < str.length(); x++) {
			if (p.x + x >= 0 && p.x <= int(world.GetConsoleWidth() / 10.6) - x &&
				p.y + y >= 0 && p.y <= int(world.GetConsoleHeight() / 24) - y) {
				world.BufferWrite(p.x + x, p.y + y, const_cast<char*>(&str.at(x)));
			}
			else
			{
				int a = str.length();
			}
		}
		y++;
	}
}

vector<string> Sprite::GetData()
{
	return data_;
}

void Sprite::SetData(vector<string> data)
{
	data_ = data;
}

ColorRGB Sprite::GetColor()
{
	return color_;
}

void Sprite::SetColor(ColorRGB color)
{
	color_ = color;
}