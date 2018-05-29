#pragma once
#include "Define.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(float dt);
	virtual void render();

	void addChild(Entity* child);
	void removeChild();

	Vec2 pos;
	Rect rect;
	bool isVisible;
	bool isRemoved;
	Entity* parent;
	vector<Entity*> children;

};