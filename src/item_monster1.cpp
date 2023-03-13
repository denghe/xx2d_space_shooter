#include "main.h"
#include "scene_game.h"
#include "item_monster1.h"

void Item_Monster1::Init2(xx::XY const& pos_, xx::Shared<xx::MovePathCache> mpc_) {
	assert(owner);
	originalPos = pos_;
	mpc = std::move(mpc_);
	frames = &owner->frames.monster1;
	radius = 7 * owner->scale;

	// init
	auto mp = mpc->Move(0);
	radians = mp->radians;
	pos = originalPos + mp->pos;
	hp = 20;

	SGCInit(&owner->monsterGrid, pos.As<int32_t>() + owner->monsterGrid.maxX / 2);

	// init draw
	body.SetScale(owner->scale);
}

bool Item_Monster1::Update() {
	auto pair = (std::pair<float, float>&)(*frames)[frameIndex]->ud;
	movedDistance += speed * pair.first;
	auto mp = mpc->Move(movedDistance);
	if (!mp) return true;
	frameStep = pair.second;

	SGCUpdate(pos.As<int32_t>() + owner->monsterGrid.maxX / 2);

	radians = mp->radians;
	pos = originalPos + mp->pos;
	UpdateFrameIndex();

	return false;
}
