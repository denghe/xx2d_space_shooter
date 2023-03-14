#pragma once
#include "sobj_plane_bullet.h"

struct Sobj_PlaneBullet1 : Sobj_PlaneBullet {
	Scene_Game* scene{};
	xx::Quad body;
	xx::XY pos{}, inc{};
	float radius{}, speed{};
	int64_t damage{};

	void Init(Scene_Game* scene_, xx::XY const& pos_, float const& radians, int64_t const& power_);
	bool Update() override;
	void Draw() override;
};
