#include "main.h"
#include "scene_game.h"
#include "sobj_space.h"

void Sobj_Space::Init(Scene_Game* scene) {
	this->scene = scene;
	body.SetFrame(scene->frames.background[0]).SetScale(scene->bgScale);
	yInc = 0.1f * scene->bgScale;
	ySize = body.texRectH * scene->bgScale;
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
