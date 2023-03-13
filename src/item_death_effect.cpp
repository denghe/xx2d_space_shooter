#include "main.h"
#include "scene_game.h"
#include "item_death_effect.h"

void Item_DeathEffect::Init(Scene_Game* const& owner_, xx::XY const& pos_, float const& scale) {
	owner = owner_;
	pos = pos_;

	body.SetPosition(pos).SetScale(owner->scale * scale).SetRotate(owner->rnd.Next<float>(M_PI * 2));
	owner->audio.Play("res/1.ogg");
}

bool Item_DeathEffect::Update() {
	frameIndex += 0.1f;
	return frameIndex >= owner->frames.effect.size();
}

void Item_DeathEffect::Draw() {
	body.SetFrame(owner->frames.effect[(size_t)frameIndex]).Draw();
}
