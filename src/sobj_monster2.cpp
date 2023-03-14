#include "main.h"
#include "scene_game.h"
#include "sobj_monster2.h"

void Sobj_Monster2::Init2(xx::XY const& pos_, float const& radians_) {
	assert(owner);
	// store args
	pos = pos_;
	radians = radians_;
	frames = &owner->frames.monster2;
	radius = 2 * owner->scale;

	// init
	inc = { std::cos(radians),std::sin(radians) };
	inc *= speed;
	avaliableFrameNumber = owner->frameNumber + 120 * 10;
	hp = 20;

	SGCInit(&owner->monsterGrid, pos.As<int32_t>() + owner->monsterGrid.maxX / 2);

	// init draw
	body.SetScale(owner->scale / 3);
}

bool Sobj_Monster2::Update() {
	pos += inc;
	SGCUpdate(pos.As<int32_t>() + owner->monsterGrid.maxX / 2);
	UpdateFrameIndex();
	return avaliableFrameNumber < owner->frameNumber;
}
