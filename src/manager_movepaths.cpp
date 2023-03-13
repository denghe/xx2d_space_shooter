#include "main.h"
#include "manager_movepaths.h"

void Manager_MovePaths::Init() {
	xx::MovePath mp;

	mp.FillCurve(true, { {0, 0}, {1500, 0}, {1500, -200}, {0, -200} });
	monsterTeam.Emplace()->Init(mp);

	xx::XY xy{ xx::engine.hw / 2, xx::engine.hh / 2 };
	mp.FillCurve(true, { {-xy.x, xy.y}, {xy.x, xy.y}, {xy.x, -xy.y}, {-xy.x, -xy.y} });	// for stuff
	stuff.Emplace()->Init(mp);

	// todo: more fill
}
