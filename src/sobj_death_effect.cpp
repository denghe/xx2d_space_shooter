#include "main.h"
#include "scene_game.h"
#include "sobj_death_effect.h"

void Sobj_DeathEffect::Init(Scene_Game* const& owner_, xx::XY const& pos_, float const& scale) {
	owner = owner_;
	pos = pos_;

	body.SetPosition(pos).SetScale(owner->scale * scale).SetRotate(owner->rnd.Next<float>(M_PI * 2));
	owner->audio.Play("res/1.ogg");
}

bool Sobj_DeathEffect::Update() {
	frameIndex += 0.1f;
	return frameIndex >= owner->frames.effect.size();
}

void Sobj_DeathEffect::Draw() {
	body.SetFrame(owner->frames.effect[(size_t)frameIndex]).Draw();
}
