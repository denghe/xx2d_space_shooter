#include "main.h"
#include "scene_menu.h"

void SceneMenu::Init(GameLooper* looper) {
	this->looper = looper;
	menu.Init();
	menu.items.emplace_back().Init(this, {-100, 100}, "play", 32, [this]() {
		this->looper->DelaySwitchTo<SceneMenu>();
	});
	menu.items.emplace_back().Init(this, {-100, -100}, "exit", 32, [this]() {
		this->looper->scene.Reset();
	});
}

int SceneMenu::Update() {
	menu.Update();

	menu.Draw();
	return 0;
}
