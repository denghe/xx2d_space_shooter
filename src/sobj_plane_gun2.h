#pragma once
#include "sobj_plane_gun.h"

struct Sobj_PlaneGun2 : Sobj_PlaneGun {
	void Init(Sobj_Plane* plane_) override;
	void Update() override;
	void LevelUp() override;
	void PowerUp() override;
	void SpeedUp() override;
};
