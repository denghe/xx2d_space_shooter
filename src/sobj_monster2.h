#pragma once
#include "main.h"
#include "sobj_monster.h"

struct Sobj_Monster2 : Sobj_Monster {
	xx::XY inc{};
	int64_t avaliableFrameNumber{};

	void Init2(xx::XY const& pos_, float const& radians_);
	bool Update() override;
};
