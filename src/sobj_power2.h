#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_Power2 {
	Scene_Game* scene{};
	xx::XY pos{};
	float speed{}, radius{};
	int typeId{};
	xx::Quad body;

	void Init(Scene_Game* const& scene_, xx::XY const& pos_, int const& typeId_);
	int Update();
	void Draw();

};
