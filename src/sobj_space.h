#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_Space {
	Scene_Game* scene{};
	xx::Quad body;
	float yPos{}, yInc{}, ySize{};
	void Init(Scene_Game* scene);
	void Update();
	void Draw();
};
