#pragma once
#include "main.h"

struct Scene_Game;
struct Sobj_LabelEffect {
	Scene_Game* scene{};
	xx::XY pos{}, inc{};
	uint8_t alpha{ 255 };
	int64_t avaliableFrameNumber{};
	xx::Label body;

	void Init(Scene_Game* const& scene_, xx::XY const& pos_, std::string_view const& txt_);
	bool Update();
	void Draw();

};
