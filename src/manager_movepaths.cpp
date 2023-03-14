#include "main.h"
#include "manager_movepaths.h"

void Manager_MovePaths::Init() {
	xx::MovePath mp;

	/*
-------|-----\
_______|_____/
-------|----------
	   |
	   |
	*/
	mp.FillCurve(true, { {0, 0}, {1500, 0}, {1500, -200}, {0, -200} });
	monsterTeam.Emplace()->Init(mp);

/*    |
   +--|--T
---+--+--+----
   +--+--+
	  |
*/
	xx::XY xy{ xx::engine.hw / 2, xx::engine.hh / 2 };
	mp.FillCurve(true, { {-xy.x, xy.y}, {xy.x, xy.y}, {xy.x, -xy.y}, {-xy.x, -xy.y} });	// for stuff
	stuff.Emplace()->Init(mp);

	// M
	mp.FillCurve(false, { {-1000, 0 }, {-500, 400 }, { 200, 0 }, { 200, -200 }, { 0, -250 }, { -200, -200 }, { -200, 0 }, { 500, 400 }, { 1000, 0 } });	// for stuff
	monsterStyleM.Emplace()->Init(mp);

	// todo: more fill
}
