#pragma once
#include "xx2d.h"
#include "xx2d_fps_viewer.h"

struct GameLooper;
struct SceneBase {
	GameLooper* looper{};
	virtual void Init(GameLooper*) = 0;
	virtual int Update() = 0;
	virtual ~SceneBase() {};
};

struct GameLooper : xx::GameLooperBase {
	xx::BMFont fnt;
	xx::FpsViewer fpsViewer;
	double timePool{};

	xx::Shared<SceneBase> scene;

	int Init() override;
	int Update() override;
};
