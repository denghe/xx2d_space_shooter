#pragma once
#include "main.h"
#include "sobj_plane_gun.h"

struct Scene_Game;
struct Sobj_Plane {
	Scene_Game* scene{};
	xx::Quad body;
	xx::XY pos{}, inc{};
	float speed{}, frame{}, radius{};
	int64_t invincibleFrameNumber{};
	xx::Shared<Sobj_PlaneGun> gun;

	void Init(Scene_Game* scene_, xx::XY const& bornPos = {}, int64_t const& invincibleTime_ = 0);
	bool Update();
	void Draw();
};
