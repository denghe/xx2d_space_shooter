#pragma once
#include "main.h"

struct Scene_Game;
struct Item_DeathEffect {
	Scene_Game* owner{};
	xx::XY pos{};
	float frameIndex{};
	xx::Quad body;

	void Init(Scene_Game* const& owner_, xx::XY const& pos_, float const& scale = 1.f);
	bool Update();
	void Draw();

};
