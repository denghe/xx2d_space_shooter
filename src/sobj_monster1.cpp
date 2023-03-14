#include "main.h"
#include "scene_game.h"
#include "sobj_monster1.h"

void Sobj_Monster1::Init2(xx::XY const& pos_, xx::Shared<xx::MovePathCache> mpc_) {
	assert(scene);
	originalPos = pos_;
	mpc = std::move(mpc_);
	frames = &scene->frames.monster1;
	radius = 7 * scene->scale;

	// init
	auto mp = mpc->Move(0);
	radians = mp->radians;
	pos = originalPos + mp->pos;
	hp = 20;

	SGCInit(&scene->monsterGrid, pos.As<int32_t>() + scene->monsterGrid.maxX / 2);

	// init draw
	body.SetScale(scene->scale);
}

bool Sobj_Monster1::Update() {
	auto pair = (std::pair<float, float>&)(*frames)[frameIndex]->ud;
	movedDistance += speed * pair.first;
	auto mp = mpc->Move(movedDistance);
	if (!mp) return true;
	frameStep = pair.second;

	SGCUpdate(pos.As<int32_t>() + scene->monsterGrid.maxX / 2);

	radians = mp->radians;
	pos = originalPos + mp->pos;
	UpdateFrameIndex();

	return false;
}
