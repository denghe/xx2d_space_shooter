#include "main.h"
#include "scene_game.h"
#include "item_bullet.h"

void Item_Bullet::Init(Scene_Game* owner_, xx::XY const& pos_, int64_t const& damage_) {
	owner = owner_;
	pos = pos_;
	damage = damage_;

	speed = 1.f * owner->scale;
	inc = { 0, speed };
	radius = 2 * owner->scale;

	body.SetFrame(owner->frames.bullet[0]).SetScale(owner->scale);
	owner->audio.Play("res/3.ogg");
}

bool Item_Bullet::Update() {

	// collision detection
	auto& g = owner->monsterGrid;
	auto p = pos.As<int32_t>() + g.maxX / 2;
	auto idx = g.PosToIndex(p);
	auto& deadMonsters = owner->tmpMonsters;
	deadMonsters.clear();
	int limit = 0x7FFFFFFF;
	g.Foreach9NeighborCells<true>(idx, [&](Item_Monster* const& m) {
		auto d = m->pos - pos;
		auto rr = (m->radius + radius) * (m->radius + radius);
		auto dd = d.x * d.x + d.y * d.y;
		if (dd < rr) {
			auto hp = m->hp;
			if (m->Hit(damage)) {
				deadMonsters.push_back(m);
			}
			damage -= hp;
			if (damage <= 0) {
				limit = 0;	// break foreach
			}
		}
		}, &limit);
	for (auto& m : deadMonsters) {
		owner->EraseMonster(m);
	}
	if (damage <= 0) return true;

	pos += inc;
	return pos.y > xx::engine.hh + 100;
}

void Item_Bullet::Draw() {
	body.SetPosition(pos).Draw();
}
