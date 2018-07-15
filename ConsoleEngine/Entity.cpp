#include "pch.h"
#include "Entity.h"

Entity::Entity() :
	pos_(0, 0), rect_(), is_visible_(true), is_removed_(false), parent_(nullptr)
{

}

Entity::~Entity()
{
	for (auto* child : children_) {
		if (child != nullptr) {
			delete child;
		}
	}
}

void Entity::Update(float dt)
{
	for (auto* child : children_) {
		child->Update(dt);
	}

	children_.erase(remove_if(children_.begin(), children_.end(), [](Entity* child) {
		if (child->is_removed_) {
			delete child;
			return true;
		}
		return false;
	}), children_.end());
}

void Entity::Render()
{
	if (!is_visible_) 
		return;

	Vec2 pos_ = this->pos_;
	if (parent_) {
		this->pos_.x += parent_->pos_.x;
		this->pos_.y += parent_->pos_.y;
	}

	for (auto& child : children_) {
		child->Render();
	}

	this->pos_ = pos_;
}

void Entity::AddChild(Entity* child)
{
	child->parent_ = this;
	children_.push_back(child);
}

void Entity::RemoveChild()
{
	is_removed_ = true;
}

Vec2 Entity::GetPos()
{
	return pos_;
}

void Entity::SetPos(Vec2 pos)
{
	pos_ = pos;
}

Rect Entity::GetRect()
{
	return rect_;
}

void Entity::SetRect(Rect rect)
{
	rect_ = rect;
}

bool Entity::GetIsVisible()
{
	return is_visible_;
}

void Entity::SetIsVisible(bool is_visible)
{
	is_visible_ = is_visible;
}

bool Entity::GetIsRemoved()
{
	return is_removed_;
}

void Entity::SetIsRemoved(bool is_removed)
{
	is_removed_ = is_removed;
}

Entity* Entity::GetParent()
{
	return parent_;
}