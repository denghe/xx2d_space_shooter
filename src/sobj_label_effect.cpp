#include "main.h"
#include "scene_game.h"
#include "sobj_label_effect.h"

void Sobj_LabelEffect::Init(Scene_Game* const& scene_, xx::XY const& pos_, std::string_view const& txt_) {
	scene = scene_;
	pos = pos_;

	avaliableFrameNumber = scene->frameNumber + 126;
	inc = { 0, 0.5 };

	body.SetText(scene->looper->fnt, txt_, 64);
}

bool Sobj_LabelEffect::Update() {
	pos += inc;
	alpha -= 2;
	return avaliableFrameNumber < scene->frameNumber;
}

void Sobj_LabelEffect::Draw() {
	body.SetPosition(pos).SetColor({ 255,255,255,alpha }).Draw();
}
