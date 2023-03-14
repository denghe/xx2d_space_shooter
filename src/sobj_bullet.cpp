#include "main.h"
#include "scene_game.h"
#include "sobj_bullet.h"

void Sobj_Bullet::Init(Scene_Game* scene_, xx::XY const& pos_, float const& radians, int64_t const& damage_) {
	scene = scene_;
	pos = pos_;
	damage = damage_;

	speed = 1.f * scene->scale;
	inc = xx::XY{ std::cos(radians), std::sin(radians) } * speed;
	radius = 2 * scene->scale;

	body.SetFrame(scene->frames.bullet[0]).SetScale(scene->scale);
	scene->audio.Play("res/3.ogg");
}

bool Sobj_Bullet::Update() {

	// collision detection
	auto& g = scene->monsterGrid;
	auto p = pos.As<int32_t>() + g.maxX / 2;
	auto idx = g.PosToIndex(p);
	auto& deadMonsters = scene->tmpMonsters;
	deadMonsters.clear();
	int limit = 0x7FFFFFFF;
	g.Foreach9NeighborCells<true>(idx, [&](Sobj_Monster* const& m) {
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
		scene->EraseMonster(m);
	}
	if (damage <= 0) return true;

	pos += inc;
	return pos.y > xx::engine.hh + 100;
}

void Sobj_Bullet::Draw() {
	body.SetPosition(pos).Draw();
}
