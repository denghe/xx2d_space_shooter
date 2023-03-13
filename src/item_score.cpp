#include "main.h"
#include "scene_game.h"
#include "item_score.h"

void Item_Score::Init(Scene_Game* const& owner_) {
	owner = owner_;
	step = 1;
}
void Item_Score::Add(int64_t const& offset) {
	to += offset;
	step = (to - from) / 120 * 2;
	if (step < 1) {
		step = 1;
	}
}
void Item_Score::Update() {
	if (from < to) {
		from += step;
		if (from > to) {
			from = to;
		}
	}
}
void Item_Score::Draw() {
	auto s = std::to_string(from);
	auto siz = s.size();
	auto& fs = owner->frames.number;
	auto wh = fs[0]->spriteSourceSize * owner->scale;
	auto origin = xx::engine.ninePoints[8];
	xx::XY xy{ origin.x - wh.x * siz / 2, origin.y - 10 };
	xx::Quad q;
	q.SetScale(owner->scale).SetAnchor({ 0, 1 });
	for (auto& c : s) {
		q.SetFrame(fs[c - '0']).SetPosition(xy).Draw();
		xy.x += wh.x;
	}
}
