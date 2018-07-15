#pragma once
#include "Sprite.h"
class Animation :
	public Sprite
{
public:
	Animation(const string& path, int frame_num_, int size = 100, float fps = 20.0f, bool loop = true);
	~Animation();

	Animation& SetData(vector<string> data);
	Animation& AddData(vector<string> data);

	void Update(float dt);
	void Render();

private:
	vector<vector<string>> datas_;
	float current_frame_;
	float fps_;
	bool loop_;
};

