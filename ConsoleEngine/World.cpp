#include "pch.h"
#include "World.h"
#include "Scene.h"
#include "TestScene.h"

World::World() : current_scene_(nullptr), is_end_(false), n_console_index_(0)
{

}

World::~World()
{

}

void World::Init()
{
	srand((unsigned)time(NULL));
	ChangeScene(new TestScene());
	ZeroMemory(current_keys_, sizeof(current_keys_));
	ZeroMemory(last_keys_, sizeof(last_keys_));
	current_clock_ = clock();
	last_clock_ = clock();

	CreateBuffer(1280, 720);
}

void World::Dispose()
{
	if (current_scene_) {
		delete current_scene_;
	}

	for (int i = 0; i < 2; i++) {
		CloseHandle(console_[i].GetConsoleHandle());
	}
}

void World::Update()
{
	last_clock_ = current_clock_;
	current_clock_ = clock();
	dt_ = (double)(current_clock_ - last_clock_) / CLOCKS_PER_SEC;

	for (int i = 0; i < 256; i++) {
		last_keys_[i] = current_keys_[i];
		current_keys_[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mouse_pos_);
	ScreenToClient(GetConsoleWindow(), &mouse_pos_);

	if (current_scene_)
		current_scene_->Update(dt_);

	for (auto* timer : timers_)
		timer->Update(dt_);

	if (GetKeyState(VK_ESCAPE) > 0) {
		is_end_ = true;
	}
}

void World::Render()
{
	if (current_scene_)
		current_scene_->Render();

	Flipping();
}

void World::Clear()
{
	console_[n_console_index_].BufferClear();
}

void World::ChangeScene(Scene* scene)
{
	if (current_scene_) {
		delete current_scene_;
	}

	current_scene_ = scene;
}

int World::GetKeyState(int vk)
{
	if (current_keys_[vk] && last_keys_[vk]) return 2;
	if (current_keys_[vk] && !last_keys_[vk]) return 1;
	if (!current_keys_[vk] && last_keys_[vk]) return -1;
	return -2;
}

Vec2 World::GetMousePos()
{
	return Vec2(mouse_pos_.x / 12, mouse_pos_.y / 24);
}

Vec2 World::GetMousePosToScene()
{
	return GetMousePos().Sub(this->current_scene_->GetPos()).VecToInt();
}

void World::CreateBuffer(int Width, int Height)
{
	console_width_ = Width;
	console_height_ = Height;
	console_[0].CreateBuffer(Width, Height);
	console_[1].CreateBuffer(Width, Height);
}

void World::BufferSetColor(ColorRGB color)
{
	console_[n_console_index_].TextColor(color);
}

void World::BufferWrite(int x, int y, char* string)
{
	console_[n_console_index_].BufferWrite(x, y, string);
}

void World::Flipping()
{
	//Sleep(33);
	SetConsoleActiveScreenBuffer(console_[n_console_index_].GetConsoleHandle());
	n_console_index_ = !n_console_index_;
}

bool World::GetIsEnd()
{
	return is_end_;
}

float World::GetDt()
{
	return dt_;
}

vector<Timer*> World::GetTimers()
{
	return timers_;
}

int World::GetConsoleWidth()
{
	return console_width_;
}

int World::GetConsoleHeight()
{
	return console_height_;
}

World world;