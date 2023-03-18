#pragma once
#include "stage.h"
// ...

struct Stage1 : Stage {
	void Init(Scene_Game* scene_) override;
	void Enter() override;
	void Leave() override;

	xx::Coro CoEnter();
	xx::Coro CoCreateMonsterTeam(xx::Shared<xx::MovePathCache> mpc, int num, int stuffTypeId);
	xx::Coro CoCreateMonsters(int n1, int n2);

	// todo: env
};
