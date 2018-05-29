#pragma once
#include "Define.h"
#include "Entity.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(string data);
	~Sprite();

	Sprite& setData(string data);
	Sprite& addData(string data);
	void render();
	
	//string datas;
	vector<string> datas;
	ColorRGB textColor;
	ColorRGB backgroundColor;
};