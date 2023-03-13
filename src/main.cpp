#include "main.h"

int GameLooper::Init() {
	fnt = xx::engine.LoadBMFont("res/font/coderscrux.fnt"sv);
	fpsViewer.Init(fnt);

	//scene = xx::Make<MainMenu::Scene>();
	//scene->Init(this);

	return 0;
}

int GameLooper::Update() {
	if (xx::engine.Pressed(xx::KbdKeys::Escape)) return 1;

	//int r = scene->Update();

	fpsViewer.Update();
	return 0;
}

int main() {
	return GameLooper{}.Run();
}
