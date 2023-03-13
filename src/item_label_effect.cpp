#include "main.h"
#include "scene_game.h"
#include "item_label_effect.h"

void Item_LabelEffect::Init(Scene_Game* const& owner_, xx::XY const& pos_, std::string_view const& txt_) {
	owner = owner_;
	pos = pos_;

	avaliableFrameNumber = owner->frameNumber + 100;
	inc = { 0, 0.5 };

	body.SetText(owner->looper->fnt, txt_, 64);
}

bool Item_LabelEffect::Update() {
	pos += inc;
	return avaliableFrameNumber < owner->frameNumber;
}

void Item_LabelEffect::Draw() {
	body.SetPosition(pos).Draw();
}
