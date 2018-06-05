#include "pch.h"
#include "Sprite.h"
#include "World.h"
#include "Scene.h"

Sprite::Sprite() : color(255, 255, 255)
{
}

Sprite::Sprite(string data) : color(255, 255, 255)
{
	setData(data);
}

Sprite::~Sprite()
{
}

Sprite& Sprite::setData(string data)
{
	datas.clear();
	datas.push_back(data);
	rect.right = data.length();
	rect.bottom = 1;
	return *this;
}

Sprite& Sprite::addData(string data)
{
	datas.push_back(data);
	rect.right = max(rect.right, data.length());
	rect.bottom++;
	return *this;
}

void Sprite::render()
{
	if (!isVisible || datas.empty()) 
		return;

	Entity::render();

	Vec2 p = this->pos;
	if (parent) {
		p.x += parent->pos.x;
		p.y += parent->pos.y;
	}

	//if (p.x - rect.right + 1 >= 0 && p.x <= int(world.consoleWidth / 10.6) - rect.right + 1 &&
	//	p.y - rect.bottom + 1 >= 0 && p.y <= int(world.consoleHeight / 24) - rect.bottom + 1) {
	//	world.bufferWrite(p.x, p.y, const_cast<char*>(data.data()));
	//}
	//영준이 열심히 한다 ! 파이팅 !!!^^♥

	world.bufferSetColor(color);

	int y = 0;
	for (string data : datas) {
		for (int x = 0; x < data.length(); x++) {
			if (p.x + x >= 0 && p.x <= int(world.consoleWidth / 10.6) - x &&
				p.y + y >= 0 && p.y <= int(world.consoleHeight / 24) - y) {
				world.bufferWrite(p.x + x, p.y + y, const_cast<char*>(&data.at(x)));
			}
		}
		y++;
	}
}