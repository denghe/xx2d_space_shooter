#pragma once
#include "main.h"

struct Manager_Frames {
	void Init();

	std::vector<xx::Shared<xx::Frame>> plane;			// p, p1 ~ 3
	std::vector<xx::Shared<xx::Frame>> number;			// n0 ~ 9
	std::vector<xx::Shared<xx::Frame>> bullet;			// b1 ~ 9
	std::vector<xx::Shared<xx::Frame>> rocket;			// r1 ~ 2
	std::vector<xx::Shared<xx::Frame>> monster1;		// ma1 ~ 6
	std::vector<xx::Shared<xx::Frame>> monster2;		// mb1 ~ 5
	std::vector<xx::Shared<xx::Frame>> monster3;		// mc1 ~ 4
	std::vector<xx::Shared<xx::Frame>> background;		// bg1
	std::vector<xx::Shared<xx::Frame>> monsterBullet;	// eb1 ~ 4
	std::vector<xx::Shared<xx::Frame>> effect;			// e1 ~ 5
	std::vector<xx::Shared<xx::Frame>> stuff;			// po1 ~ 3, ph, ps, pc
	std::vector<xx::Shared<xx::Frame>> text;			// tstart, tgameover

	xx::Shared<xx::GLTexture> texRing, texStar;		// p11.png   p1.png
	xx::Shared<xx::ParticleConfig> particleCfg;
};
