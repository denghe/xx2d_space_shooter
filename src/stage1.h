#pragma once
#include "stage.h"
// ...

struct Stage1 : Stage {
	void Init(Scene_Game* scene_) override;
	void Enter() override;
	void Leave() override;

	xx::Coro CoShowTitle();
	xx::Coro CoEnter();
	xx::Coro CoCreateMonsterTeam(int n, int64_t bonus);
	xx::Coro CoPlaneReborn(xx::XY deathPos = {}, xx::XY bornPos = {});

	// todo: env
};
