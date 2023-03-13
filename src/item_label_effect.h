#pragma once
#include "main.h"

struct Scene_Game;
struct Item_LabelEffect {
	Scene_Game* owner{};
	xx::XY pos{}, inc{};
	int64_t avaliableFrameNumber{};
	xx::Label body;

	void Init(Scene_Game* const& owner_, xx::XY const& pos_, std::string_view const& txt_);
	bool Update();
	void Draw();

};
