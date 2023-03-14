#include "main.h"
#include "scene_game.h"
#include "stage5.h"

void Stage5::Init(Scene_Game* scene_) {
	scene = scene_;
}

void Stage5::Enter() {
	scene->coros.Add(CoEnter());
}

void Stage5::Leave() {
}

xx::Coro Stage5::CoEnter() {
	
	scene->coros.Add(scene->CoShowStageTitle("stage 5"));				// show stage title

	for (size_t i = 0; i < 10; i++) {
		scene->coros.Add(CoCreateMonsterTeam(1, 2000));					// make some monster1 team
		CoSleep(0.5s);
	}
	
	scene->coros.Add(CoCreateMonsters(120 * 5, 10));					// make some random monster2
	
	CoSleep(10s);														// wait some time

	scene->stages.GoNext();												// next stage
}

xx::Coro Stage5::CoCreateMonsters(int n1, int n2) {
	// i: num frames
	for (int i = 0; i < n1; i++) {

		// j: num monsters per frame
		for (int j = 0; j < n2; j++) {

			auto radians = scene->rnd.Next<float>(0, M_PI);
			xx::XY v{ std::cos(radians),std::sin(radians) };
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

xx::Coro Stage5::CoCreateMonsterTeam(int n, int64_t bonus) {
	// team death counter
	auto dt = xx::Make<Listener<Sobj_Monster>>([this, n, bonus](Sobj_Monster* m) mutable {
		if (--n == 0) {
			scene->score.Add(bonus);
			scene->labels.emplace_back().Emplace()->Init(scene, m->pos, xx::ToString("+", bonus));	// show label effect
			scene->powers.emplace_back().Emplace()->Init(scene, m->pos, scene->stuffTypeId++);	// drop P
			if (scene->stuffTypeId >= scene->frames.stuff.size()) {
				scene->stuffTypeId = 0;
			}
		}
	});
	// create team members
	for (int i = 0; i < n; i++) {
		auto m = xx::Make<Sobj_Monster1>();
		m->Init1(scene, 4.f, { 255,255,255,255 }, dt);
		m->Init2({ -1000, 300 }, scene->movePaths.monsterTeam);
		scene->AddMonster(m);
		CoSleep(600ms);
	}
}
