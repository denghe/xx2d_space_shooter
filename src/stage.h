#pragma once
#include "main.h"

struct Scene_Game;
struct Stage {
	virtual void Init(Scene_Game* scene_) = 0;
	virtual void Enter() = 0;
	virtual void Leave() = 0;
	virtual ~Stage() {};

	Scene_Game* scene{};
};

struct Stages {
	Scene_Game* scene{};
	int cursor{};
	std::vector<xx::Shared<Stage>> ss;
	void Init(Scene_Game* scene_);
	void GoNext();
};
