#pragma once
#include "main.h"

struct Scene_Game;
struct Item_Bullet {
	Scene_Game* owner{};
	xx::Quad body;
	xx::XY pos{}, inc{};
	float radius{}, speed{};
	int64_t damage{};

	void Init(Scene_Game* owner_, xx::XY const& pos_, int64_t const& power_);
	bool Update();
	void Draw();
};
