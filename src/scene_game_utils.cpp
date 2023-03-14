#include "main.h"
#include "scene_game.h"

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

xx::Coro Scene_Game::CoPlaneReborn(xx::XY bornPos, std::chrono::steady_clock::duration const& delay) {
	CoSleep(delay);
	assert(!plane);
	plane.Emplace()->Init(this, bornPos, 240);
}
