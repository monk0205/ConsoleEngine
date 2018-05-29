#pragma once
#include "Define.h"
#include "Scene.h"
#include "Sprite.h"

class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

	void update(float dt);
	void render();

	void charMove(float dt);
	void cameraMove(float dt);

	void pointCollision();

	Sprite* charSpr;
	Sprite* pointSpr[2];
};