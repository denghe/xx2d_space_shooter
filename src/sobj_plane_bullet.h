#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_PlaneBullet {
	Scene_Game* scene{};
	virtual bool Update() = 0;
	virtual void Draw() = 0;
	virtual ~Sobj_PlaneBullet() {}
};
