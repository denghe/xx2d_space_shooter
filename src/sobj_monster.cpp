#include "main.h"
#include "scene_game.h"
#include "sobj_monster.h"

void Sobj_Monster::Init1(Scene_Game* owner_, float const& speed_, xx::RGBA8 const& color_, Listener_s<Sobj_Monster> deathListener_) {
	assert(!owner);
	owner = owner_;
	speed = speed_;
	color = color_;
	deathListener = std::move(deathListener_);
	frameStep = 0.1f;
}

void Sobj_Monster::UpdateFrameIndex() {
	frameIndex += frameStep;
	if (frameIndex >= frames->size()) {
		frameIndex = 0;
	}
}

bool Sobj_Monster::Hit(int64_t const& damage) {
	hp -= damage;
	if (hp <= 0) {
		owner->score.Add(100);
		owner->deathEffects.emplace_back().Emplace()->Init(owner, pos, radius / owner->scale / 7);	// show death effect
		if (deathListener) {
			(*deathListener)(this);
		}
		return true;
	}
	hitEffectExpireFrameNumber = owner->frameNumber + 10;
	return false;
}
void Sobj_Monster::Draw() {
	body.SetPosition(pos).SetRotate(-radians + float(M_PI / 2)).SetFrame((*frames)[frameIndex])
		.SetColor(hitEffectExpireFrameNumber > owner->frameNumber ? xx::RGBA8{ 255,0,0,255 } : color)
		.Draw();
}

Sobj_Monster::~Sobj_Monster() {}
