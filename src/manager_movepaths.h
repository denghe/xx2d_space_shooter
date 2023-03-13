#pragma once
#include "main.h"

struct Manager_MovePaths {
	void Init();

	xx::Shared<xx::MovePathCache> monsterTeam;
	xx::Shared<xx::MovePathCache> stuff;

	std::vector<xx::Shared<xx::MovePathCache>> monsters;
};
