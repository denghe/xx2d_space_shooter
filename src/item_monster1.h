#pragma once
#include "main.h"
#include "item_monster.h"

struct Item_Monster1 : Item_Monster {
	xx::Shared<xx::MovePathCache> mpc;
	xx::XY originalPos{};
	float movedDistance{};

	void Init2(xx::XY const& pos_, xx::Shared<xx::MovePathCache> mpc_);
	bool Update() override;
};
