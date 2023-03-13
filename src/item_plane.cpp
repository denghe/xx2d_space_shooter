#include "main.h"
#include "scene_game.h"
#include "item_plane.h"

void Item_Plane::Init(Scene_Game* owner, xx::XY const& bornPos, int64_t const& invincibleTime) {
	this->owner = owner;
	pos = bornPos;
	inc = {};
	level = 1;
	speed = 0.5f * owner->scale;
	frame = 2;	// 1 ~ 3
	radius = 7 * owner->scale;
	invincibleFrameNumber = owner->frameNumber + invincibleTime;
	fireCD = 20;
	bulletDamage = 10;

	body.SetFrame(owner->frames.plane[1]).SetScale(owner->scale);
}

bool Item_Plane::Update() {

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
	owner->lastPlanePos = pos;
	//}

	if (invincibleFrameNumber <= owner->frameNumber) {
		// collision detection with monster
		for (auto& m : owner->monsters) {
			auto d = m->pos - pos;
			auto rr = (m->radius + radius) * (m->radius + radius);
			auto dd = d.x * d.x + d.y * d.y;
			if (dd < rr) {
				owner->deathEffects.emplace_back().Emplace()->Init(owner, pos);	// show death effect
				return true;
			}
		}
	}

	// collision detection with P
	for (auto i = (ptrdiff_t)owner->powers.size() - 1; i >= 0; --i) {
		auto& o = owner->powers[i];
		auto d = o->pos - pos;
		auto rr = (o->radius + radius) * (o->radius + radius);
		auto dd = d.x * d.x + d.y * d.y;
		if (dd < rr) {
			switch (o->typeId) {
			case 0:
				level += 5;
				owner->labels.emplace_back().Emplace()->Init(owner, pos, xx::ToString("level up!"));	// show label effect
				break;
			case 1:
				fireCD /= 2;
				owner->labels.emplace_back().Emplace()->Init(owner, pos, xx::ToString("reduce fire CD!"));	// show label effect
				break;
			case 2:
				bulletDamage += 10;
				owner->labels.emplace_back().Emplace()->Init(owner, pos, xx::ToString("bullet damage up!"));	// show label effect
				break;
			case 3:
				speed *= 2;
				owner->labels.emplace_back().Emplace()->Init(owner, pos, xx::ToString("speed up!"));	// show label effect
				break;
			default:
				throw std::logic_error("unhandled typeId");
			}
			o = owner->powers.back();
			owner->powers.pop_back();
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
	if (fireableFrameNumber < owner->frameNumber) {
		fireableFrameNumber = owner->frameNumber + fireCD;
		auto step = 2 * owner->scale;
		float x = -level / 2 * step;
		for (int i = 0; i < level; i++) {
			auto&& b = owner->bullets.emplace_back().Emplace();
			b->Init(owner, pos + xx::XY{ x + i * step, 8 * owner->scale }, bulletDamage);
		}
	}

	return false;
}

void Item_Plane::Draw() {
	body.SetFrame(owner->frames.plane[size_t(frame + 0.5f)])
		.SetPosition(pos)
		.SetColor(invincibleFrameNumber > owner->frameNumber ? xx::RGBA8{ 127,127,127,220 } : xx::RGBA8{ 255,255,255,255 })
		.Draw();
}
