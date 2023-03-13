#pragma once
#include "main.h"

struct Scene_Game;
struct Item_Power {
	Scene_Game* owner{};
	xx::Shared<xx::MovePathCache> mpc;
	xx::XY pos{}, inc{};
	float movedDistance{}, speed{}, radius{};
	int lineNumber{}, typeId{}, i{};
	xx::Quad body;

	void Init(Scene_Game* const& owner_, xx::XY const& pos_, int const& typeId_);
	int Update();
	void Draw();

};
