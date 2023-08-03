#pragma once
#include "main.h"

struct Scene_Game;

// important: memory can't move !!!  container need reserve !!!
struct Sobj_ExplodeEffect {
	xx::Particle particle;
	xx::Quad ring;
	xx::XY pos;
	xx::Tasks actions;
	xx::Task<> Action_ScaleTo(float s, float step);
	xx::Task<> Action_FadeOut(uint8_t step);
	xx::Task<> Action_Explode();
	void Init(Scene_Game* scene_, xx::XY const& pos_);
	bool Update();
	void Draw1();
	void Draw2();
};
