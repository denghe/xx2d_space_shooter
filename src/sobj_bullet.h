#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_Bullet {
	Scene_Game* scene{};
	xx::Quad body;
	xx::XY pos{}, inc{};
	float radius{}, speed{};
	int64_t damage{};

	void Init(Scene_Game* scene_, xx::XY const& pos_, float const& radians, int64_t const& power_);
	bool Update();
	void Draw();
};
