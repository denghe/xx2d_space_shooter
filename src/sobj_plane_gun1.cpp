#include "main.h"
#include "scene_game.h"
#include "sobj_plane.h"
#include "sobj_plane_bullet1.h"
#include "sobj_plane_gun1.h"

void Sobj_PlaneGun1::Init(Sobj_Plane* plane_) {
	plane = plane_;
	scene = plane->scene;

	level = 1;
	fireCD = 20;
	bulletDamage = 10;
}

void Sobj_PlaneGun1::Update() {
	if (fireableFrameNumber < scene->frameNumber) {
		fireableFrameNumber = scene->frameNumber + fireCD;
		auto step = 2 * scene->scale;
		float x = -level / 2 * step;
		for (int i = 0; i < level; i++) {
			auto b = xx::Make<Sobj_PlaneBullet1>();
			b->Init(scene, plane->pos + xx::XY{ x + i * step, 8 * scene->scale }, M_PI_2, bulletDamage);
			scene->bullets.emplace_back(std::move(b));
		}
	}
}

// todo: limit

void Sobj_PlaneGun1::LevelUp() {
	level += 2;
	scene->labels.emplace_back().Emplace()->Init(scene, plane->pos, xx::ToString("gun level up!"));	// show label effect
}

void Sobj_PlaneGun1::PowerUp() {
	bulletDamage += 10;
	scene->labels.emplace_back().Emplace()->Init(scene, plane->pos, xx::ToString("bullet damage up!"));	// show label effect
}

void Sobj_PlaneGun1::SpeedUp() {
	fireCD /= 2;
	scene->labels.emplace_back().Emplace()->Init(scene, plane->pos, xx::ToString("fire speed up!"));	// show label effect
}
