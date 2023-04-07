#include "main.h"
#include "scene_game.h"
#include "stage.h"
// ...

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
	// ...

	// play bg music
	//audio.PlayBG("res/bg.ogg");

	// run stage
	stages.Init(this);

	// init plane
	coros.Add(CoPlaneReborn({}, 0s));
}

/***********************************************************************/

int Scene_Game::Update() {

	minXY = { -xx::engine.hw - 100, -xx::engine.hh - 100 };
	maxXY = { xx::engine.hw + 100, xx::engine.hh + 100 };

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
			coros.Add(CoPlaneReborn(plane->pos));	// reborn
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
		for (auto i = (ptrdiff_t)power2s.size() - 1; i >= 0; --i) {
			auto& o = power2s[i];
			if (o->Update()) {
				o = power2s.back();
				power2s.pop_back();
			}
		}

		// calc death effects
		for (auto i = (ptrdiff_t)deathEffects.size() - 1; i >= 0; --i) {
			auto& o = deathEffects[i];
			if (o->Update()) {
				o = deathEffects.back();
				deathEffects.pop_back();
			}
		}

		// calc explodes
		explodes.Foreach([](auto& o) { return o->Update(); });

		// refresh score
		score.Update();

		// ...
	}

	space.Draw();
	for (auto& o : monsters) o->Draw();
	if (plane) plane->Draw();
	explodes.Foreach([](auto& o) { o->Draw1(); });
	explodes.Foreach([](auto& o) { o->Draw2(); });
	for (auto& o : deathEffects) o->Draw();
	for (auto& o : bullets) o->Draw();
	for (auto& o : power2s) o->Draw();
	for (auto& o : powers) o->Draw();
	for (auto& o : labels) o->Draw();
	score.Draw();
	if (stageTitle) stageTitle->Draw();
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
	assert(m->scene);
	assert(m->scene == this);
	m->SGCTryRemove();
	auto idx = m->indexAtOwnerMonsters;
	m->indexAtOwnerMonsters = std::numeric_limits<size_t>::max();
	m->scene = {};
	assert(monsters[idx] == m);
	monsters[idx] = monsters.back();
	monsters.back()->indexAtOwnerMonsters = idx;
	monsters.pop_back();
}

/***********************************************************************/

xx::Coro Scene_Game::CoPlaneReborn(xx::XY bornPos, std::chrono::steady_clock::duration const& delay) {
	CoSleep(delay);
	assert(!plane);
	plane.Emplace()->Init(this, bornPos, 240);
}

xx::Coro Scene_Game::CoShowStageTitle(std::string_view const& txt) {
	auto&& lb = stageTitle.Emplace();									// create title

	lb->SetColor({ 255, 127, 127, 255 }).SetPosition({ 0, 200 })
		.SetText(looper->fnt, txt, 128);								// set properties

	CoSleep(1s);														// show & wait 1s

	for (int i = 255; i >= 0; i -= 2) {
		lb->SetColor({ 255, 127, 127, (uint8_t)i });					// fade out
		CoYield;
	}

	lb.Reset();															// release
}
