#pragma once
#include "Define.h"
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"

class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

	void Update(float dt);
	void Render();

	void charMove(float dt);
	void cameraMove(float dt);

	void pointCollision();

	Animation* charSpr;
	Sprite* pointSpr[2];
	Sprite* spr;
};