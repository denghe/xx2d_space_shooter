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

	// load move path config file, fill to monsters
	xx::CurvesPointsCollection cpsc;
	auto [d, p] = xx::engine.LoadFileData("res/movepath.bin");
	if (int r = d.Read(cpsc)) {
		throw std::logic_error(xx::ToString("read CurvesPointsCollection from ", p, " error! r = ", r));
	}
	monsters.reserve(cpsc.data.size());
	for (auto& cps : cpsc.data) {
		mp.Clear();
		mp.FillCurve(cps.isLoop, cps.points);

		auto mpc = xx::Make<xx::MovePathCache>();
		mpc->Init(mp, 1);
		monsters.emplace_back(std::move(cps.name), std::move(mpc));
	}
}

xx::Shared<xx::MovePathCache> const& Manager_MovePaths::operator[](size_t const& idx) const {
	return monsters[idx].second;
}

xx::Shared<xx::MovePathCache> const& Manager_MovePaths::operator[](std::string_view const& name) const {
	for (auto& pair : monsters) {
		if (pair.first == name) {
			return pair.second;
		}
	}
	throw std::logic_error(xx::ToString("can't find movepath: ", name));
}
