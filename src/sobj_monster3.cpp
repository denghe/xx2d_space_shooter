#include "main.h"
#include "scene_game.h"
#include "sobj_monster3.h"

void Sobj_Monster3::Init2(xx::XY const& pos_) {
	assert(scene);
	//// store args
	//pos = pos_;
	//radians = radians_;
	//frames = &scene->frames.monster3;
	//radius = 2 * scene->scale;

	//// init
	//inc = { std::cos(radians),std::sin(radians) };
	//inc *= speed;
	//avaliableFrameNumber = scene->frameNumber + 120 * 10;
	//hp = 20;

	//SGCInit(&scene->monsterGrid, pos.As<int32_t>() + scene->monsterGrid.maxX / 2);

	//// init draw
	//body.SetScale(scene->scale / 3);
}

bool Sobj_Monster3::Update() {
	// todo: keeping follow plane

	//pos += inc;
	//SGCUpdate(pos.As<int32_t>() + scene->monsterGrid.maxX / 2);
	//UpdateFrameIndex();
	//return avaliableFrameNumber < scene->frameNumber;
	return false;
}
