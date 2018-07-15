#include "pch.h"
#include "TestScene.h"
#include "World.h"

TestScene::TestScene()
{
	spr = new Sprite();
	spr->AddStr("*****");
	spr->SetPos(Vec2(50, 20));
	AddChild(spr);

	charSpr = new Animation("Resource/tmpAni", 6, 10, 20.0f);

	charSpr->SetPos(Vec2(10, 10));
	charSpr->SetColor(ColorRGB(67, 218, 236));
	AddChild(charSpr);

	for (int i = 0; i < 2; i++) {
		pointSpr[i] = new Sprite();
		pointSpr[i]->SetPos(Vec2(20, 20));
		AddChild(pointSpr[i]);

		pointSpr[i]->SetIsVisible(false);
	}
	pointSpr[0]->SetIsVisible(true);

	pointSpr[0]->SetStr("&");
	pointSpr[1]->SetStr("@");
}

TestScene::~TestScene()
{
}

void TestScene::Render()
{
	Entity::Render();

	Vec2 MP = world.GetMousePosToScene();
	stringstream str;
	str << MP.x << ", " << MP.y;
	world.BufferWrite(0, 1, const_cast<char*>(str.str().c_str()));
}

void TestScene::Update(float dt)
{
	Entity::Update(dt);

	if (world.GetKeyState(VK_RETURN) == 1) {
		charSpr->RemoveChild();
	}

	charMove(dt);
	cameraMove(dt);

	if (world.GetKeyState(VK_LBUTTON) > 0) {
		charSpr->SetColor(ColorRGB(255, 255, 255));
	}
	else {
		charSpr->SetColor(ColorRGB(67, 218, 236));
	}

	pointCollision();
}

void TestScene::charMove(float dt)
{
	float moveSpeed = 10 * dt;
	Vec2 pos = charSpr->GetPos();
	if (world.GetKeyState('W') > 0) {
		pos.y -= moveSpeed;
	}
	if (world.GetKeyState('S') > 0) {
		pos.y += moveSpeed;
	}
	if (world.GetKeyState('A') > 0) {
		pos.x -= moveSpeed;
	}
	if (world.GetKeyState('D') > 0) {
		pos.x += moveSpeed;
	}
	charSpr->SetPos(pos);
}

void TestScene::cameraMove(float dt)
{
	float moveSpeed = 10 * dt;

	Vec2 pos = GetPos();
	if (world.GetKeyState(VK_UP) > 0) {
		pos.y += moveSpeed;
	}
	if (world.GetKeyState(VK_DOWN) > 0) {
		pos.y -= moveSpeed;
	}
	if (world.GetKeyState(VK_LEFT) > 0) {
		pos.x += moveSpeed;
	}
	if (world.GetKeyState(VK_RIGHT) > 0) {
		pos.x -= moveSpeed;
	}
	SetPos(pos);
}

void TestScene::pointCollision()
{
	Rect MR = Rect(0, 0, 1, 1);
	Vec2 MP = world.GetMousePosToScene();
	stringstream str;
	str << MP.x << ", " << MP.y;
	world.BufferWrite(0, 1, const_cast<char*>(str.str().c_str()));
	if(pointSpr[0]->GetRect().Offset(pointSpr[0]->GetPos()).IntersectsRect(MR, MP)){
	//if (pointSpr[0]->rect_.Offset(pointSpr[0]->pos_).IntersectsRect(charSpr->rect_, charSpr->pos_)) {
		//pointSpr[0]->is_visible_ = false;
		//pointSpr[1]->is_visible_ = true;
		pointSpr[0]->SetColor(ColorRGB(255, 0, 0));
	}
	else {
		//pointSpr[0]->is_visible_ = true;
		//pointSpr[1]->is_visible_ = false;
		pointSpr[0]->SetColor(ColorRGB(0, 255, 128));
	}
}