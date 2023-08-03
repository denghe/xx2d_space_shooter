#pragma once
#include "stage.h"
// ...

struct Stage3 : Stage {
	void Init(Scene_Game* scene_) override;
	void Enter() override;
	void Leave() override;

	xx::Task<> CoEnter();
	xx::Task<> CoCreateMonsterTeam(int n, int64_t bonus);
	xx::Task<> CoCreateMonsters(int n1, int n2);

	// todo: env
};
