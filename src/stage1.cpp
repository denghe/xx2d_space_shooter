#include "main.h"
#include "scene_game.h"
#include "stage1.h"

void Stage1::Init(Scene_Game* scene_) {
	scene = scene_;
}

void Stage1::Enter() {
	scene->coros.Add(CoEnter());
}

void Stage1::Leave() {
}

xx::Coro Stage1::CoEnter() {
	
	scene->coros.Add(scene->CoShowStageTitle("stage 1"));				// show stage title

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-1a"sv], 5, 3));
	CoSleep(4s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-1b"sv], 5, 0));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-2a"sv], 5, 1));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-2b"sv], 5, 2));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-3a"sv], 5, 3));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-3b"sv], 5, 4));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-4a"sv], 5, 0));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-4b"sv], 5, 1));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-5a"sv], 5, 2));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-5b"sv], 5, 0));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-6a"sv], 5, 1));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsterTeam(scene->movePaths["s1-6b"sv], 5, 2));
	CoSleep(3s);

	scene->coros.Add(CoCreateMonsters(120 * 5, 10));					// make some random monster2
	CoSleep(10s);

	scene->stages.GoNext();
}

xx::Coro Stage1::CoCreateMonsters(int n1, int n2) {
	// i: num frames
	for (int i = 0; i < n1; i++) {

		// j: num monsters per frame
		for (int j = 0; j < n2; j++) {

			auto radians = scene->rnd.Next<float>(0, M_PI);
			xx::XY v{ std::cos(radians), std::sin(radians) };
			auto bornPos = v * (xx::engine.hw + 200);
			auto d = scene->lastPlanePos - bornPos;
			radians = std::atan2(d.y, d.x);

			auto m = xx::Make<Sobj_Monster2>();
			m->Init1(scene, 2.f, { 255,255,255,255 });
			m->Init2(bornPos, radians);
			scene->AddMonster(m);
		}

		CoYield;	// step frame
	}
}

xx::Coro Stage1::CoCreateMonsterTeam(xx::Shared<xx::MovePathCache> mpc, int n, int stuffTypeId) {
	// team death counter
	auto dt = xx::Make<Listener<Sobj_Monster>>([this, n, stuffTypeId](Sobj_Monster* m) mutable {
		if (--n == 0) {
			scene->power2s.emplace_back().Emplace()->Init(scene, m->pos, stuffTypeId);	// all dead: drop stuff
		}
	});
	// create team members
	for (int i = 0; i < n; i++) {
		auto m = xx::Make<Sobj_Monster1>();
		m->Init1(scene, 4.f, { 255,255,255,255 }, dt);
		m->Init2({}, mpc);
		scene->AddMonster(m);
		CoSleep(600ms);
	}
}
