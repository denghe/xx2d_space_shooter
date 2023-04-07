#include "main.h"
#include "manager_frames.h"

void Manager_Frames::Init() {
	// res preload
	xx::TP tp;
	tp.Fill("res/space_shooter.plist");

	tp.GetTo(plane, { "p" });
	tp.GetToByPrefix(plane, "p");
	tp.GetToByPrefix(number, "n");
	tp.GetToByPrefix(bullet, "b");
	tp.GetToByPrefix(rocket, "r");
	tp.GetToByPrefix(monster1, "ma");
	tp.GetToByPrefix(monster2, "mb");
	tp.GetToByPrefix(monster3, "mc");
	tp.GetToByPrefix(background, "bg");
	tp.GetToByPrefix(monsterBullet, "eb");
	tp.GetToByPrefix(effect, "e");
	tp.GetToByPrefix(stuff, "po");
	tp.GetTo(stuff, { "ps", "ph", "pc" });
	tp.GetTo(text, { "tstart", "tgameover" });

	// set frame delay & move speed
	(std::pair<float, float>&)monster1[0]->ud = { 0.5f, 0.1f };
	(std::pair<float, float>&)monster1[1]->ud = { 0.7f, 0.05f };
	(std::pair<float, float>&)monster1[2]->ud = { 1.0f, 0.02f };
	(std::pair<float, float>&)monster1[3]->ud = { 0.7f, 0.05f };
	(std::pair<float, float>&)monster1[4]->ud = { 0.4f, 0.07f };
	(std::pair<float, float>&)monster1[5]->ud = { 0.2f, 0.1f };

	texStar = xx::engine.LoadSharedTexture("res/p1.png");
	xx::GLTexParm(*texStar, GL_LINEAR);
	texRing = xx::engine.LoadSharedTexture("res/p11.png");
	xx::GLTexParm(*texRing, GL_LINEAR);

	particleCfg.Emplace();
	particleCfg->sprite.SetTexture(texStar);
	particleCfg->emission = 500;
	particleCfg->lifetime = 0.05f;
	particleCfg->particleLife = { 0.15f, 0.25f };
	particleCfg->direction = 0;
	particleCfg->spread = M_PI * 2;
	particleCfg->relative = {};
	particleCfg->speed = { 0.f, 250.f };
	particleCfg->gravity = { 0.f, 250.f };
	particleCfg->radialAccel = { -130.f, 200.f };
	particleCfg->tangentialAccel = { -200.f, 270.f };
	particleCfg->size = { 0.2f, 0.4f };
	particleCfg->sizeVar = 0.4;
	particleCfg->spin = {};
	particleCfg->spinVar = 0;
	particleCfg->color = { { 1, 0.3, 0.3, 1 },{ 1, 1, 1, 0.7 } };
	particleCfg->colorVar = 0.5;
	particleCfg->alphaVar = 1;
}
