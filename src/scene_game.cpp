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
	audio.PlayBG("res/bg.ogg");

	// run stage
	stages.Init(this);

	// init plane
	coros.Add(CoPlaneReborn({}, 0s));
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
	if (stageTitle) stageTitle->Draw();
	// ...


	return 0;
}
