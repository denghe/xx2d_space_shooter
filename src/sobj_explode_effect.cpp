#include "main.h"
#include "scene_game.h"
#include "sobj_explode_effect.h"

xx::Coro Sobj_ExplodeEffect::Action_ScaleTo(float s, float step) {
	CoYield;
	for (; ring.scale.x < s; ring.scale += step) {
		CoYield;
	}
	ring.scale = { s, s };
}

xx::Coro Sobj_ExplodeEffect::Action_FadeOut(uint8_t step) {
	CoYield;
	for (; ring.color.a >= step; ring.color.a -= step) {
		CoYield;
	}
	ring.color.a = 0;
}

xx::Coro Sobj_ExplodeEffect::Action_Explode() {
	particle.FireAt(pos);
	do {
		particle.Update(1.f / 120);
		CoYield;
	} while (!particle.Empty());
}

void Sobj_ExplodeEffect::Init(Scene_Game* scene_, xx::XY const& pos_) {
	pos = pos_;
	ring.SetPosition(pos).SetScale(0.01).SetTexture(scene_->frames.texRing).SetColorA((uint8_t)200);
	particle.Init(scene_->frames.particleCfg, 20);
	actions.Add(Action_ScaleTo(3.f, 3.f / 30));
	actions.Add(Action_FadeOut(255 / 30));
	actions.Add(Action_Explode());
}

bool Sobj_ExplodeEffect::Update() {
	return !actions();
}

void Sobj_ExplodeEffect::Draw1() {
	ring.Draw();
}

void Sobj_ExplodeEffect::Draw2() {
	particle.Draw();
}
