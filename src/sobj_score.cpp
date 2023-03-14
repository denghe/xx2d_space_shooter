#include "main.h"
#include "scene_game.h"
#include "sobj_score.h"

void Sobj_Score::Init(Scene_Game* const& scene_) {
	scene = scene_;
	step = 1;
}
void Sobj_Score::Add(int64_t const& offset) {
	to += offset;
	step = (to - from) / 120 * 2;
	if (step < 1) {
		step = 1;
	}
}
void Sobj_Score::Update() {
	if (from < to) {
		from += step;
		if (from > to) {
			from = to;
		}
	}
}
void Sobj_Score::Draw() {
	auto s = std::to_string(from);
	auto siz = s.size();
	auto& fs = scene->frames.number;
	auto wh = fs[0]->spriteSourceSize * scene->scale;
	auto origin = xx::engine.ninePoints[8];
	xx::XY xy{ origin.x - wh.x * siz / 2, origin.y - 10 };
	xx::Quad q;
	q.SetScale(scene->scale).SetAnchor({ 0, 1 });
	for (auto& c : s) {
		q.SetFrame(fs[c - '0']).SetPosition(xy).Draw();
		xy.x += wh.x;
	}
}
