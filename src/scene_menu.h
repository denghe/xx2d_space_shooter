#pragma once
#include "main.h"

struct SceneMenu : SceneBase {
	Menu menu;
	void Init(GameLooper* looper) override;
	int Update() override;
};
