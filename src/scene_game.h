#pragma once
#include "main.h"
#include "manager_frames.h"
#include "manager_movepaths.h"
#include "item_bullet.h"
#include "item_death_effect.h"
#include "item_label_effect.h"
#include "item_monster.h"
#include "item_monster1.h"
#include "item_monster2.h"
#include "item_plane.h"
#include "item_power.h"
#include "item_score.h"
#include "item_space.h"
// ...

struct Scene_Game : SceneBase {
	void Init(GameLooper* looper) override;
	int Update() override;

	xx::Coro SceneLogic();
	xx::Coro SceneLogic_CreateMonsterTeam(int n, int64_t bonus);
	xx::Coro SceneLogic_PlaneReborn(xx::XY deathPos = {}, xx::XY bornPos = {});

	void AddMonster(Item_Monster* m);	// insert into monsters & sync index
	void EraseMonster(Item_Monster* m);	// remove from monsters & clear index


	Manager_Frames frames;
	Manager_MovePaths movePaths;

	Item_Space space;
	Item_Score score;

	xx::Shared<Item_Plane> plane;

	std::vector<xx::Shared<Item_Bullet>> bullets;

	xx::SpaceGridC<Item_Monster> monsterGrid;			// ensure life cycle > monsters
	std::vector<xx::Shared<Item_Monster>> monsters;
	std::vector<Item_Monster*> tmpMonsters;

	std::vector<xx::Shared<Item_LabelEffect>> labels;

	std::vector<xx::Shared<Item_Power>> powers;

	std::vector<xx::Shared<Item_DeathEffect>> deathEffects;

	// ...

	xx::Audio audio;

	xx::Coros coros;

	float timePool{};
	float bgScale{}, scale{};
	int64_t frameNumber{};
	xx::XY lastPlanePos{};
	xx::Rnd rnd;
	int stuffIndex{};
};
