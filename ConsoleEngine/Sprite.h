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

	Sprite& SetStr(string str);
	Sprite& AddStr(string str);
	void Render();

	vector<string> GetData();
	void SetData(vector<string> data);
	ColorRGB GetColor();
	void SetColor(ColorRGB color);
	
private:
	vector<string> data_;
	ColorRGB color_;
};