#pragma once
#include "main.h"

struct Scene_Game;
struct Item_Score {
	Scene_Game* owner{};
	int64_t from{}, to{}, step{};

	void Init(Scene_Game* const& owner_);
	void Add(int64_t const& offset);
	void Update();
	void Draw();

};
