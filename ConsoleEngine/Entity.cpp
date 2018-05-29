#include "pch.h"
#include "Entity.h"

Entity::Entity() :
	pos(0, 0), rect(), isVisible(true), isRemoved(false), parent(nullptr)
{

}

Entity::~Entity()
{
	for (auto* child : children) {
		if (child != nullptr) {
			delete child;
		}
	}
}

void Entity::update(float dt)
{
	for (auto* child : children) {
		child->update(dt);
	}

	children.erase(remove_if(children.begin(), children.end(), [](Entity* child) {
		if (child->isRemoved) {
			delete child;
			return true;
		}
		return false;
	}), children.end());
}

void Entity::render()
{
	if (!isVisible) 
		return;

	Vec2 pos = this->pos;
	if (parent) {
		this->pos.x += parent->pos.x;
		this->pos.y += parent->pos.y;
	}

	for (auto& child : children) {
		child->render();
	}

	this->pos = pos;
}

void Entity::addChild(Entity* child)
{
	child->parent = this;
	children.push_back(child);
}

void Entity::removeChild()
{
	isRemoved = true;
}