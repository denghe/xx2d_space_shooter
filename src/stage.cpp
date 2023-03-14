#include "main.h"
#include "stage.h"
#include "stage1.h"
// ...

void Stages::Init(Scene_Game* scene_) {
	scene = scene_;
	ss.emplace_back(xx::Make<Stage1>())->Init(scene);
	// ...

	ss[0]->Enter();
}

void Stages::GoNext() {
	ss[cursor]->Leave();
	if (++cursor >= ss.size()) {
		cursor = 0;
	}
	ss[cursor]->Enter();
}
