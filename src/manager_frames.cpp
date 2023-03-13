#include "main.h"
#include "manager_frames.h"

void Manager_Frames::Init() {
	// res preload
	xx::TP tp;
	tp.Fill("res/space_shooter.plist");

	tp.GetTo(plane, { "p" });
	tp.GetToByPrefix(plane, "p");
	tp.GetToByPrefix(number, "n");
	tp.GetToByPrefix(bullet, "b");
	tp.GetToByPrefix(rocket, "r");
	tp.GetToByPrefix(monster1, "ma");
	tp.GetToByPrefix(monster2, "mb");
	tp.GetToByPrefix(monster3, "mc");
	tp.GetToByPrefix(background, "bg");
	tp.GetToByPrefix(monsterBullet, "eb");
	tp.GetToByPrefix(effect, "e");
	tp.GetToByPrefix(stuff, "po");
	tp.GetTo(stuff, { "ps", "ph", "pc" });
	tp.GetTo(text, { "tstart", "tgameover" });

	// set frame delay & move speed
	(std::pair<float, float>&)monster1[0]->ud = { 0.5f, 0.1f };
	(std::pair<float, float>&)monster1[1]->ud = { 0.7f, 0.05f };
	(std::pair<float, float>&)monster1[2]->ud = { 1.0f, 0.02f };
	(std::pair<float, float>&)monster1[3]->ud = { 0.7f, 0.05f };
	(std::pair<float, float>&)monster1[4]->ud = { 0.4f, 0.07f };
	(std::pair<float, float>&)monster1[5]->ud = { 0.2f, 0.1f };
}
