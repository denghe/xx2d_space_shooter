#include "main.h"
#include "scene_game.h"
#include "sobj_space.h"

void Sobj_Space::Init(Scene_Game* owner) {
	this->owner = owner;
	body.SetFrame(owner->frames.background[0]).SetScale(owner->bgScale);
	yInc = 0.1f * owner->bgScale;
	ySize = body.texRectH * owner->bgScale;
}

void Sobj_Space::Update() {
	yPos += yInc;
	if (yPos > ySize) {
		yPos -= ySize;
	}
}

void Sobj_Space::Draw() {
	body.SetPositionY(-yPos).Draw();
	body.SetPositionY(-yPos + ySize).Draw();
}
