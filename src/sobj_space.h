#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_Space {
	Scene_Game* owner{};
	xx::Quad body;
	float yPos{}, yInc{}, ySize{};
	void Init(Scene_Game* owner);
	void Update();
	void Draw();
};
