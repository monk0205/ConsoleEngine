#include "pch.h"
#include "TestScene.h"
#include "World.h"

TestScene::TestScene()
{
	charSpr = new Sprite();
	charSpr->addData("***************")
		    .addData("*             *")
		    .addData("*             *")
		    .addData("*             *")
		    .addData("*             *")
		    .addData("***************");
	charSpr->pos = Vec2(10, 10);
	charSpr->color = ColorRGB(67, 218, 236);
	addChild(charSpr);

	for (int i = 0; i < 2; i++) {
		pointSpr[i] = new Sprite();
		pointSpr[i]->pos = Vec2(20, 20);
		addChild(pointSpr[i]);

		pointSpr[i]->isVisible = false;
	}
	pointSpr[0]->isVisible = true;

	pointSpr[0]->setData("&");
	pointSpr[1]->setData("@");
}

TestScene::~TestScene()
{
}

void TestScene::render()
{
	Entity::render();

	Vec2 MP = world.getMousePosToScene();
	stringstream str;
	str << MP.x << ", " << MP.y;
	world.bufferWrite(0, 1, const_cast<char*>(str.str().c_str()));
}

void TestScene::update(float dt)
{
	Entity::update(dt);

	if (world.getKeyState(VK_RETURN) == 1) {
		charSpr->removeChild();
	}

	charMove(dt);
	cameraMove(dt);

	if (world.getKeyState(VK_LBUTTON) > 0) {
		charSpr->color = ColorRGB(255, 255, 255);
	}
	else {
		charSpr->color = ColorRGB(67, 218, 236);
	}

	pointCollision();
}

void TestScene::charMove(float dt)
{
	float moveSpeed = 10 * dt;
	if (world.getKeyState('W') > 0) {
		charSpr->pos.y -= moveSpeed;
	}
	if (world.getKeyState('S') > 0) {
		charSpr->pos.y += moveSpeed;
	}
	if (world.getKeyState('A') > 0) {
		charSpr->pos.x -= moveSpeed;
	}
	if (world.getKeyState('D') > 0) {
		charSpr->pos.x += moveSpeed;
	}
}

void TestScene::cameraMove(float dt)
{
	float moveSpeed = 10 * dt;

	if (world.getKeyState(VK_UP) > 0) {
		this->pos.y += moveSpeed;
	}
	if (world.getKeyState(VK_DOWN) > 0) {
		this->pos.y -= moveSpeed;
	}
	if (world.getKeyState(VK_LEFT) > 0) {
		this->pos.x += moveSpeed;
	}
	if (world.getKeyState(VK_RIGHT) > 0) {
		this->pos.x -= moveSpeed;
	}
}

void TestScene::pointCollision()
{
	Rect MR = Rect(0, 0, 1, 1);
	Vec2 MP = world.getMousePosToScene();
	stringstream str;
	str << MP.x << ", " << MP.y;
	world.bufferWrite(0, 1, const_cast<char*>(str.str().c_str()));
	if(pointSpr[0]->rect.offset(pointSpr[0]->pos).intersectsRect(MR, MP)){
	//if (pointSpr[0]->rect.offset(pointSpr[0]->pos).intersectsRect(charSpr->rect, charSpr->pos)) {
		//pointSpr[0]->isVisible = false;
		//pointSpr[1]->isVisible = true;
		pointSpr[0]->color = ColorRGB(255, 0, 0);
	}
	else {
		//pointSpr[0]->isVisible = true;
		//pointSpr[1]->isVisible = false;
		pointSpr[0]->color = ColorRGB(0, 255, 128);
	}
}