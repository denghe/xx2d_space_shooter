#include "main.h"
#include "scene_game.h"
#include "sobj_plane.h"
#include "sobj_plane_gun1.h"
#include "sobj_plane_gun2.h"
// ...

void Sobj_Plane::Init(Scene_Game* scene, xx::XY const& bornPos, int64_t const& invincibleTime) {
	this->scene = scene;
	pos = bornPos;
	inc = {};
	speed = 0.8f * scene->scale;
	frame = 2;	// 1 ~ 3
	radius = 7 * scene->scale;
	invincibleFrameNumber = scene->frameNumber + invincibleTime;

	gun = xx::Make<Sobj_PlaneGun1>();
	gun->Init(this);

	body.SetFrame(scene->frames.plane[1]).SetScale(scene->scale);
}

bool Sobj_Plane::Update() {

	// move body
	//if (xx::engine.Pressed(xx::Mbtns::Left) || xx::engine.Pressed(xx::Mbtns::Right)) {
	auto x = pos.x;	// bak for change frame compare
	auto& mp = xx::engine.mousePosition;
	auto d = mp - pos;
	auto dd = d.x * d.x + d.y * d.y;
	if (speed * speed > dd) {
		inc = {};
		pos = mp;
	} else {
		inc = d.As<float>() / std::sqrt(float(dd)) * speed;
		pos += inc;
	}
	scene->lastPlanePos = pos;
	//}

	if (invincibleFrameNumber <= scene->frameNumber) {
		// collision detection with monster
		for (auto& m : scene->monsters) {
			auto d = m->pos - pos;
			auto rr = (m->radius + radius) * (m->radius + radius);
			auto dd = d.x * d.x + d.y * d.y;
			if (dd < rr) {
				scene->deathEffects.emplace_back().Emplace()->Init(scene, pos);	// show death effect
				return true;
			}
		}
	}

	// collision detection with P
	for (auto i = (ptrdiff_t)scene->powers.size() - 1; i >= 0; --i) {
		auto& o = scene->powers[i];
		if (TryEatPower(o->pos, o->radius, o->typeId)) {
			o = scene->powers.back();
			scene->powers.pop_back();
		}
	}
	for (auto i = (ptrdiff_t)scene->power2s.size() - 1; i >= 0; --i) {
		auto& o = scene->power2s[i];
		if (TryEatPower(o->pos, o->radius, o->typeId)) {
			o = scene->power2s.back();
			scene->power2s.pop_back();
		}
	}

	// change frame display
	constexpr float finc = 0.1f, fmin = 1.f, fmid = 2.f, fmax = 3.f;
	if (x < pos.x) {
		frame += finc;
		if (frame > fmax) {
			frame = fmax;
		}
	} else if (x > pos.x) {
		frame -= finc;
		if (frame < fmin) {
			frame = fmin;
		}
	} else {
		if (frame > fmid) {
			frame -= finc;
			if (frame < fmid) {
				frame = fmid;
			}
		} else if (frame < fmid) {
			frame += finc;
			if (frame > fmid) {
				frame = fmid;
			}
		}
	}

	// auto shoot
	gun->Update();

	return false;
}

bool Sobj_Plane::TryEatPower(xx::XY const& powerPos, float const& powerRadius, int const& powerTypeId) {
	auto d = powerPos - pos;
	auto rr = (powerRadius + radius) * (powerRadius + radius);
	auto dd = d.x * d.x + d.y * d.y;
	if (dd < rr) {
		switch (powerTypeId) {
		case 0:
			gun->LevelUp();
			break;
		case 1:
			gun->SpeedUp();
			break;
		case 2:
			gun->PowerUp();
			break;
		case 3:
			speed *= 2;
			scene->labels.emplace_back().Emplace()->Init(scene, pos, xx::ToString("move speed up!"));	// show label effect
			break;
		case 4:
		{
			auto newGun = xx::Make<Sobj_PlaneGun2>();
			newGun->InitFrom(gun.pointer);
			gun = std::move(newGun);
			scene->labels.emplace_back().Emplace()->Init(scene, pos, xx::ToString("change to gun 2!"));	// show label effect
			break;
		}
		case 5:
		{
			auto newGun = xx::Make<Sobj_PlaneGun1>();
			newGun->InitFrom(gun.pointer);
			gun = std::move(newGun);
			scene->labels.emplace_back().Emplace()->Init(scene, pos, xx::ToString("change to gun 1!"));	// show label effect
			break;
		}
		default:
			throw std::logic_error("unhandled typeId");
		}
		return true;
	}
	return false;
}

void Sobj_Plane::Draw() {
	body.SetFrame(scene->frames.plane[size_t(frame + 0.5f)])
		.SetPosition(pos)
		.SetColor(invincibleFrameNumber > scene->frameNumber ? xx::RGBA8{ 127,127,127,220 } : xx::RGBA8{ 255,255,255,255 })
		.Draw();
}
