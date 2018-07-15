#pragma once
#include "Define.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float dt);
	virtual void Render();

	void AddChild(Entity* child);
	void RemoveChild();

	Vec2 GetPos();
	void SetPos(Vec2 pos);

	Rect GetRect();
	void SetRect(Rect rect);

	bool GetIsVisible();
	void SetIsVisible(bool is_visisble);

	bool GetIsRemoved();
	void SetIsRemoved(bool is_removed);

	Entity* GetParent();

private:
	Vec2 pos_;
	Rect rect_;
	bool is_visible_;
	bool is_removed_;
	Entity* parent_;
	vector<Entity*> children_;
};