#include "main.h"
#include "scene_game.h"
#include "stage3.h"

void Stage3::Init(Scene_Game* scene_) {
	scene = scene_;
}

void Stage3::Enter() {
	scene->tasks.AddTask(CoEnter());
}

void Stage3::Leave() {
}

xx::Task<> Stage3::CoEnter() {
	
	scene->tasks.AddTask(scene->CoShowStageTitle("stage 3"));				// show stage title

	for (size_t i = 0; i < 10; i++) {
		scene->tasks.AddTask(CoCreateMonsterTeam(1, 2000));					// make some monster1 team
		co_await xx::engine.TaskSleep(0.5);
	}
	
	scene->tasks.AddTask(CoCreateMonsters(120 * 5, 10));					// make some random monster2
	
	co_await xx::engine.TaskSleep(10);									// wait some time

	scene->stages.GoNext();												// next stage
}

xx::Task<> Stage3::CoCreateMonsters(int n1, int n2) {
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

		co_yield 0;	// step frame
	}
}

xx::Task<> Stage3::CoCreateMonsterTeam(int n, int64_t bonus) {
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
		co_await xx::engine.TaskSleep(0.6);
	}
}
