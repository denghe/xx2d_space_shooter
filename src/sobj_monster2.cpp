#include "main.h"
#include "scene_game.h"
#include "sobj_monster2.h"

void Sobj_Monster2::Init2(xx::XY const& pos_, float const& radians_) {
	assert(scene);
	// store args
	pos = pos_;
	radians = radians_;
	frames = &scene->frames.monster2;
	radius = 2 * scene->scale;

	// init
	inc = { std::cos(radians),std::sin(radians) };
	inc *= speed;
	avaliableFrameNumber = scene->frameNumber + 120 * 10;
	hp = 20;

	SGCInit(&scene->monsterGrid, pos.As<int32_t>() + scene->monsterGrid.maxX / 2);

	// init draw
	body.SetScale(scene->scale / 3);
}

bool Sobj_Monster2::Update() {
	pos += inc;
	SGCUpdate(pos.As<int32_t>() + scene->monsterGrid.maxX / 2);
	UpdateFrameIndex();
	return avaliableFrameNumber < scene->frameNumber;
}
