#include "main.h"
#include "stage.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"
#include "stage6.h"
// ...

void Stages::Init(Scene_Game* scene_) {
	scene = scene_;
	ss.emplace_back(xx::Make<Stage1>())->Init(scene);
	ss.emplace_back(xx::Make<Stage2>())->Init(scene);
	ss.emplace_back(xx::Make<Stage3>())->Init(scene);
	ss.emplace_back(xx::Make<Stage4>())->Init(scene);
	ss.emplace_back(xx::Make<Stage5>())->Init(scene);
	ss.emplace_back(xx::Make<Stage6>())->Init(scene);
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
