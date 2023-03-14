#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_DeathEffect {
	Scene_Game* scene{};
	xx::XY pos{};
	float frameIndex{};
	xx::Quad body;

	void Init(Scene_Game* const& scene_, xx::XY const& pos_, float const& scale = 1.f);
	bool Update();
	void Draw();

};
