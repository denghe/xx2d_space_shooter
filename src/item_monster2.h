#pragma once
#include "main.h"
#include "item_monster.h"

struct Item_Monster2 : Item_Monster {
	xx::XY inc{};
	int64_t avaliableFrameNumber{};

	void Init2(xx::XY const& pos_, float const& radians_);
	bool Update() override;
};
