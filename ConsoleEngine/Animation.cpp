#include "pch.h"
#include "Animation.h"


Animation::Animation(const string& path, int frame_num, int size, float fps, bool loop) : datas_(0), fps_(fps), loop_(loop)
{
	for (int i = 0; i < frame_num; i++) {
		vector<string> vs;
		ifstream fin(path + "/" + to_string(i) + ".txt");
		string str;
		while (getline(fin, str)) {
			vs.push_back(str);
		}
		AddData(vs);
	}
}


Animation::~Animation()
{
}

Animation& Animation::SetData(vector<string> data)
{
	datas_.clear();
	datas_.push_back(data);
	Rect rect = GetRect();
	for (string str : datas_.front()) {
		rect.right = max(rect.right, str.length());
	}
	rect.bottom = datas_.front().size();
	SetRect(rect);
	return *this;
}

Animation& Animation::AddData(vector<string> data)
{
	datas_.push_back(data);
	Rect rect = GetRect();
	for (string str : datas_.front()) {
		rect.right = max(rect.right, str.length());
	}
	rect.bottom = datas_.front().size();
	SetRect(rect);
	return *this;
}

void Animation::Update(float dt)
{
	Sprite::Update(dt);

	current_frame_ += dt * fps_;

	if ((int)current_frame_ >= datas_.size()) {
		if (loop_) {
			current_frame_ = 0;
		}
		else {
			current_frame_ = datas_.size() - 1;
		}
	}

	Sprite::SetData(datas_[int(current_frame_)]);
}

void Animation::Render()
{
	Sprite::Render();
}