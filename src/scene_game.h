﻿#pragma once
#include "main.h"
#include "manager_frames.h"
#include "manager_movepaths.h"
#include "sobj_plane_bullet.h"
#include "sobj_death_effect.h"
#include "sobj_label_effect.h"
#include "sobj_monster.h"
#include "sobj_monster1.h"
#include "sobj_monster2.h"
#include "sobj_plane.h"
#include "sobj_power.h"
#include "sobj_power2.h"
#include "sobj_score.h"
#include "sobj_space.h"
#include "sobj_explode_effect.h"
// ...
#include "stage.h"
// ...

struct Scene_Game : SceneBase {
	void Init(GameLooper* looper) override;
	int Update() override;


	Manager_Frames frames;
	Manager_MovePaths movePaths;

	Sobj_Space space;
	Sobj_Score score;

	xx::Shared<Sobj_Plane> plane;

	std::vector<xx::Shared<Sobj_PlaneBullet>> bullets;

	xx::SpaceGridC<Sobj_Monster> monsterGrid;			// ensure life cycle > monsters
	std::vector<xx::Shared<Sobj_Monster>> monsters;
	std::vector<Sobj_Monster*> tmpMonsters;

	std::vector<xx::Shared<Sobj_LabelEffect>> labels;
	xx::ListLink<xx::Shared<Sobj_ExplodeEffect>> explodes;

	std::vector<xx::Shared<Sobj_Power>> powers;
	std::vector<xx::Shared<Sobj_Power2>> power2s;

	std::vector<xx::Shared<Sobj_DeathEffect>> deathEffects;

	xx::Shared<xx::SimpleLabel> stageTitle;	// manage by stage
	// ...

	xx::Audio audio;

	xx::Tasks tasks;

	Stages stages;

	float timePool{};
	float bgScale{}, scale{};
	int64_t frameNumber{};
	xx::XY lastPlanePos{};
	xx::Rnd rnd;
	int stuffTypeId{};

	xx::XY minXY{}, maxXY{};	// for screen display bonding box check


	// utils
	xx::Task<> CoShowStageTitle(std::string_view const& txt);
	xx::Task<> CoPlaneReborn(xx::XY bornPos = {}, double const& delay = 3);

	void AddMonster(Sobj_Monster* m);	// insert into monsters & sync index
	void EraseMonster(Sobj_Monster* m);	// remove from monsters & clear index
};
