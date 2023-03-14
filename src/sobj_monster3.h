#pragma once
#include "main.h"
#include "sobj_monster.h"

struct Sobj_Plane;
struct Sobj_Monster3 : Sobj_Monster {
	xx::XY pos;
	xx::Weak<Sobj_Plane> tar;
	float speed{}, radians{};

	void Init2(xx::XY const& pos_);
	bool Update() override;
};
