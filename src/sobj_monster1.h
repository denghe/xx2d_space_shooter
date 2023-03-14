#pragma once
#include "main.h"
#include "sobj_monster.h"

struct Sobj_Monster1 : Sobj_Monster {
	xx::Shared<xx::MovePathCache> mpc;
	xx::XY originalPos{};
	float movedDistance{};

	void Init2(xx::XY const& pos_, xx::Shared<xx::MovePathCache> mpc_);
	bool Update() override;
};
