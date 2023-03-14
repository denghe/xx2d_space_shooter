#include "main.h"
#include "scene_game.h"

void Scene_Game::Init(GameLooper* looper) {
	this->looper = looper;
	frames.Init();
	movePaths.Init();

	// set env
	bgScale = xx::engine.w / frames.background[0]->spriteSourceSize.x;
	scale = bgScale / 4;

	monsterGrid.Init(500, 500, 64);

	// init all
	space.Init(this);
	score.Init(this);
	plane.Emplace()->Init(this);
	// ...

	// play bg music
	audio.PlayBG("res/bg.ogg");

	// run script
	coros.Add(SceneLogic());

}

/***********************************************************************/

int Scene_Game::Update() {

	timePool += xx::engine.delta;
	while (timePool >= 1.f / 120) {
		timePool -= 1.f / 120;

		// step frame counter
		++frameNumber;

		// generate monsters
		coros();

		// move bg
		space.Update();

		// move player's plane
		if (plane && plane->Update()) {
			coros.Add(SceneLogic_PlaneReborn(plane->pos, plane->pos));	// reborn
			plane.Reset();
		}

		// move bullets & collision detection
		for (auto i = (ptrdiff_t)bullets.size() - 1; i >= 0; --i) {
			auto& o = bullets[i];
			if (o->Update()) {
				o = bullets.back();
				bullets.pop_back();
			}
		}

		// move monster's bullets & collision detection
		// todo

		// move monsters & collision detection
		for (auto i = (ptrdiff_t)monsters.size() - 1; i >= 0; --i) {
			auto& o = monsters[i];
			if (o->Update()) {
				EraseMonster(o);
			}
		}

		// move labels
		for (auto i = (ptrdiff_t)labels.size() - 1; i >= 0; --i) {
			auto& o = labels[i];
			if (o->Update()) {
				o = labels.back();
				labels.pop_back();
			}
		}

		// move powers
		for (auto i = (ptrdiff_t)powers.size() - 1; i >= 0; --i) {
			auto& o = powers[i];
			o->lineNumber = o->Update();
			if (o->lineNumber == 0) {
				o = powers.back();
				powers.pop_back();
			}
		}

		// show death effects
		for (auto i = (ptrdiff_t)deathEffects.size() - 1; i >= 0; --i) {
			auto& o = deathEffects[i];
			if (o->Update()) {
				o = deathEffects.back();
				deathEffects.pop_back();
			}
		}

		// refresh score
		score.Update();

		// ...
	}

	space.Draw();
	for (auto& o : monsters) o->Draw();
	if (plane) plane->Draw();
	for (auto& o : deathEffects) o->Draw();
	for (auto& o : bullets) o->Draw();
	for (auto& o : powers) o->Draw();
	for (auto& o : labels) o->Draw();
	score.Draw();
	// ...


	return 0;
}

/***********************************************************************/

void Scene_Game::AddMonster(Sobj_Monster* m) {
	m->indexAtOwnerMonsters = monsters.size();
	monsters.emplace_back(m);
}

void Scene_Game::EraseMonster(Sobj_Monster* m) {
	assert(m);
	assert(m->owner);
	assert(m->owner == this);
	m->SGCTryRemove();
	auto idx = m->indexAtOwnerMonsters;
	m->indexAtOwnerMonsters = std::numeric_limits<size_t>::max();
	m->owner = {};
	assert(monsters[idx] == m);
	monsters[idx] = monsters.back();
	monsters.back()->indexAtOwnerMonsters = idx;
	monsters.pop_back();
}

/***********************************************************************/

xx::Coro Scene_Game::SceneLogic() {
	while (true) {
		for (size_t i = 0; i < 30; i++) {
			coros.Add(SceneLogic_CreateMonsterTeam(1, 2000));
			CoSleep(0.5s);
		}
		{
			int n1 = 120 * 5, n2 = 50;
			for (int i = 0; i < n1; i++) {
				for (int j = 0; j < n2; j++) {
					auto radians = rnd.Next<float>(0, M_PI);
					xx::XY v{ std::cos(radians),std::sin(radians) };
					auto bornPos = v * (xx::engine.hw + 200);
					auto d = lastPlanePos - bornPos;
					radians = std::atan2(d.y, d.x);
					auto m = xx::Make<Sobj_Monster2>();
					m->Init1(this, 2.f, { 255,255,255,255 });
					m->Init2(bornPos, radians);
					AddMonster(m);
				}
				CoYield;	//CoSleep(50ms);
			}
		}
		// ...
	}
}

xx::Coro Scene_Game::SceneLogic_CreateMonsterTeam(int n, int64_t bonus) {
	auto dt = xx::Make<Listener<Sobj_Monster>>([this, n, bonus](Sobj_Monster* m) mutable {
		if (--n == 0) {
			score.Add(bonus);
			labels.emplace_back().Emplace()->Init(this, m->pos, xx::ToString("+", bonus));	// show label effect
			powers.emplace_back().Emplace()->Init(this, m->pos, stuffIndex++);	// drop P
			if (stuffIndex == 4) {
				stuffIndex = 0;
			}
		}
		});
	for (int i = 0; i < n; i++) {
		auto m = xx::Make<Sobj_Monster1>();
		m->Init1(this, 4.f, { 255,255,255,255 }, dt);
		m->Init2({ -1000, 300 }, movePaths.monsterTeam);
		AddMonster(m);
		CoSleep(600ms);
	}
}

xx::Coro Scene_Game::SceneLogic_PlaneReborn(xx::XY deathPos, xx::XY bornPos) {
	CoSleep(3s);
	assert(!plane);
	plane.Emplace()->Init(this, bornPos, 240);
}
