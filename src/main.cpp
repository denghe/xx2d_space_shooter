#include "main.h"
#include "scene_menu.h"

void GameLooper::Init() {
	fnt = xx::engine.LoadBMFont("res/coderscrux.fnt"sv);
	fpsViewer.Init(fnt);

	scene = xx::Make<Scene_Menu>();
	scene->Init(this);
}

int GameLooper::Update() {
	if (xx::engine.Pressed(xx::KbdKeys::Escape)) return 1;

	if (!scene) return 1;
	if (int r = scene->Update()) return r;

	fpsViewer.Update();
	return 0;
}

int main() {
	return GameLooper{}.Run();
}
