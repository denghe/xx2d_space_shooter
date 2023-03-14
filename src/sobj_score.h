#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_Score {
	Scene_Game* scene{};
	int64_t from{}, to{}, step{};

	void Init(Scene_Game* const& scene_);
	void Add(int64_t const& offset);
	void Update();
	void Draw();

};
