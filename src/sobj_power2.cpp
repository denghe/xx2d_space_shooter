#include "main.h"
#include "scene_game.h"
#include "sobj_power2.h"

void Sobj_Power2::Init(Scene_Game* const& scene_, xx::XY const& pos_, int const& typeId_) {
	scene = scene_;
	pos = pos_;
	typeId = typeId_;
	speed = 0.2f * scene->scale;
	radius = 5 * scene->scale;

	body.SetFrame(scene->frames.stuff[typeId]).SetScale(scene->scale);
}

int Sobj_Power2::Update() {
	pos.y -= speed;
	return pos.y < -xx::engine.hh - 100;
}

void Sobj_Power2::Draw() {
	body.SetPosition(pos).Draw();
}
