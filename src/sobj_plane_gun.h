#pragma once
#include "main.h"

struct Sobj_Plane;
struct Scene_Game;
struct Sobj_PlaneGun {
	Sobj_Plane* plane{};
	Scene_Game* scene{};
	int64_t level{}, fireCD{}, bulletDamage{}, fireableFrameNumber{};

	virtual void InitFrom(Sobj_PlaneGun* o);
	virtual void Init(Sobj_Plane* plane_) = 0;
	virtual void Update() = 0;
	virtual void LevelUp() = 0;
	virtual void PowerUp() = 0;
	virtual void SpeedUp() = 0;
	virtual ~Sobj_PlaneGun() {}
};
