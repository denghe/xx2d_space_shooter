#include "main.h"
#include "scene_game.h"
#include "sobj_power.h"

void Sobj_Power::Init(Scene_Game* const& scene_, xx::XY const& pos_, int const& typeId_) {
	scene = scene_;
	pos = pos_;
	typeId = typeId_;

	speed = 4.f;
	radius = 5 * scene->scale;
	mpc = scene->movePaths.stuff;

	auto& tar = mpc->points[0].pos;
	inc = (tar - pos).Normalize() * speed;

	body.SetFrame(scene->frames.stuff[typeId]).SetScale(scene->scale);
}

int Sobj_Power::Update() {
	COR_BEGIN
		for (i = 0; i < 60; ++i) {	// wait 0.5 sec
			COR_YIELD
		}
	while (true) {
		pos += inc;	// move to path first point
		{
			auto d = mpc->points[0].pos - pos;
			if (d.x * d.x + d.y * d.y <= speed * speed) goto LabLoop;
		}
		COR_YIELD
	}
LabLoop:
	while (true) {
		movedDistance += speed;
		{
			auto&& mp = mpc->Move(movedDistance);
			if (!mp) COR_EXIT;
			pos = mp->pos;	// move by path
		}
		COR_YIELD
	}
	COR_END
}

void Sobj_Power::Draw() {
	body.SetPosition(pos).Draw();
}
