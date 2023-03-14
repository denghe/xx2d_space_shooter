#include "main.h"
#include "scene_game.h"
#include "sobj_plane.h"
#include "sobj_plane_gun2.h"

void Sobj_PlaneGun2::Init(Sobj_Plane* plane_) {
	plane = plane_;
	scene = plane->scene;

	level = 1;
	fireCD = 20;
	bulletDamage = 10;
}

void Sobj_PlaneGun2::Update() {
	if (fireableFrameNumber < scene->frameNumber) {
		fireableFrameNumber = scene->frameNumber + fireCD;

		float r{ M_PI_2 };
		scene->bullets.emplace_back( ).Emplace()->Init(scene, plane->pos + xx::XY{ 0, 8 * scene->scale }, r, bulletDamage);
		for (size_t i = 1; i <= level; ++i) {
			auto r1 = r + 0.1f * (float)i;
			scene->bullets.emplace_back().Emplace()->Init(scene, plane->pos + xx::XY{ 0, 8 * scene->scale }, r1, bulletDamage);
			auto r2 = r - 0.1f * (float)i;
			scene->bullets.emplace_back().Emplace()->Init(scene, plane->pos + xx::XY{ 0, 8 * scene->scale }, r2, bulletDamage);
		}
	}
}

// todo: limit

void Sobj_PlaneGun2::LevelUp() {
	level += 1;
	scene->labels.emplace_back().Emplace()->Init(scene, plane->pos, xx::ToString("gun level up!"));	// show label effect
}

void Sobj_PlaneGun2::PowerUp() {
	bulletDamage += 10;
	scene->labels.emplace_back().Emplace()->Init(scene, plane->pos, xx::ToString("bullet damage up!"));	// show label effect
}

void Sobj_PlaneGun2::SpeedUp() {
	fireCD /= 2;
	scene->labels.emplace_back().Emplace()->Init(scene, plane->pos, xx::ToString("fire speed up!"));	// show label effect
}
