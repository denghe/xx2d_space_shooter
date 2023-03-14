#pragma once
#include "stage.h"
// ...

struct Stage5 : Stage {
	void Init(Scene_Game* scene_) override;
	void Enter() override;
	void Leave() override;

	xx::Coro CoEnter();
	xx::Coro CoCreateMonsterTeam(int n, int64_t bonus);
	xx::Coro CoCreateMonsters(int n1, int n2);

	// todo: env
};
