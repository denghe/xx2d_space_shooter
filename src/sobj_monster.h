#pragma once
#include "main.h"

template<typename T>
using Listener = std::function<void(T*)>;
template<typename T>
using Listener_s = xx::Shared<Listener<T>>;

struct Scene_Game;
struct Sobj_Monster : xx::SpaceGridCItem<Sobj_Monster> {
	Scene_Game* scene{};
	size_t indexAtOwnerMonsters{ std::numeric_limits<size_t>::max() };

	xx::XY pos{};
	float radius{}, radians{}, speed{}, frameIndex{}, frameStep{};
	int64_t hp{}, maxHP{}, hitEffectExpireFrameNumber{};

	Listener_s<Sobj_Monster> deathListener;
	std::vector<xx::Shared<xx::Frame>>* frames{};
	xx::Quad body;
	xx::RGBA8 color;

	void Init1(Scene_Game* scene_, float const& speed_ = 1.f, xx::RGBA8 const& color_ = { 255,255,255,255 }, Listener_s<Sobj_Monster> deathListener_ = {});
	virtual bool Update() = 0;
	void UpdateFrameIndex();
	bool Hit(int64_t const& damage);	// return true: dead
	void Draw();
	virtual ~Sobj_Monster();
};
