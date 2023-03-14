#include "main.h"
#include "scene_game.h"
#include "sobj_death_effect.h"

void Sobj_DeathEffect::Init(Scene_Game* const& scene_, xx::XY const& pos_, float const& scale) {
	scene = scene_;
	pos = pos_;

	body.SetPosition(pos).SetScale(scene->scale * scale).SetRotate(scene->rnd.Next<float>(M_PI * 2));
	scene->audio.Play("res/1.ogg");
}

bool Sobj_DeathEffect::Update() {
	frameIndex += 0.1f;
	return frameIndex >= scene->frames.effect.size();
}

void Sobj_DeathEffect::Draw() {
	body.SetFrame(scene->frames.effect[(size_t)frameIndex]).Draw();
}
