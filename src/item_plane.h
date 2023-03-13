#pragma once
#include "main.h"

struct Scene_Game;
struct Item_Plane {
	Scene_Game* owner{};
	xx::Quad body;
	xx::XY pos{}, inc{};
	float speed{}, frame{}, radius{};
	int64_t level{}, fireCD{}, bulletDamage{}, fireableFrameNumber{}, invincibleFrameNumber{};

	void Init(Scene_Game* owner_, xx::XY const& bornPos = {}, int64_t const& invincibleTime_ = 0);
	bool Update();
	void Draw();

};
