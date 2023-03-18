#pragma once
#include "main.h"

struct Manager_MovePaths {
	void Init();

	xx::Shared<xx::MovePathCache> monsterStyleM;
	xx::Shared<xx::MovePathCache> monsterTeam;
	xx::Shared<xx::MovePathCache> stuff;

	std::vector<std::pair<std::string, xx::Shared<xx::MovePathCache>>> monsters;
	xx::Shared<xx::MovePathCache> const& operator[](size_t const& idx) const;
	xx::Shared<xx::MovePathCache> const& operator[](std::string_view const& name) const;
};
