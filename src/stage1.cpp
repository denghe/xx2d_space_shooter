#include "main.h"
#include "stage1.h"
#include "scene_game.h"

void Stage1::Init(Scene_Game* scene_) {
	scene = scene_;
}

void Stage1::Enter() {
	scene->coros.Add(CoEnter());
}

void Stage1::Leave() {
}

xx::Coro Stage1::CoShowTitle() {
	auto&& lb = scene->stageTitle.Emplace();
	lb->SetColor({ 255, 127, 127, 255 }).SetPosition({ 0, 200 }).SetText(scene->looper->fnt, "stage 1", 128);
	CoSleep(2s);
	lb.Reset();
}

xx::Coro Stage1::CoEnter() {

	scene->coros.Add(CoShowTitle());

	while (true) {
		for (size_t i = 0; i < 30; i++) {
			scene->coros.Add(CoCreateMonsterTeam(1, 2000));
			CoSleep(0.5s);
		}
		{
			int n1 = 120 * 5, n2 = 50;
			for (int i = 0; i < n1; i++) {
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
				CoYield;	//CoSleep(50ms);
			}
		}
		// ...
	}
}

xx::Coro Stage1::CoCreateMonsterTeam(int n, int64_t bonus) {
	auto dt = xx::Make<Listener<Sobj_Monster>>([this, n, bonus](Sobj_Monster* m) mutable {
		if (--n == 0) {
			scene->score.Add(bonus);
			scene->labels.emplace_back().Emplace()->Init(scene, m->pos, xx::ToString("+", bonus));	// show label effect
			scene->powers.emplace_back().Emplace()->Init(scene, m->pos, scene->stuffIndex++);	// drop P
			if (scene->stuffIndex == 4) {
				scene->stuffIndex = 0;
			}
		}
	});
	for (int i = 0; i < n; i++) {
		auto m = xx::Make<Sobj_Monster1>();
		m->Init1(scene, 4.f, { 255,255,255,255 }, dt);
		m->Init2({ -1000, 300 }, scene->movePaths.monsterTeam);
		scene->AddMonster(m);
		CoSleep(600ms);
	}
}
