#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_Power {
	Scene_Game* scene{};
	xx::Shared<xx::MovePathCache> mpc;
	xx::XY pos{}, inc{};
	float movedDistance{}, speed{}, radius{};
	int lineNumber{}, typeId{}, i{};
	xx::Quad body;

	void Init(Scene_Game* const& scene_, xx::XY const& pos_, int const& typeId_);
	int Update();
	void Draw();

};
