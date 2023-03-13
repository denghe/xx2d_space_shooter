#pragma once
#include "xx2d.h"

struct SceneBase;
struct MenuItem;
using MenuItem_MouseEventListener = xx::MouseEventListener<MenuItem*>;

struct MenuItem {
	bool HandleMouseDown(MenuItem_MouseEventListener& L);
	int HandleMouseMove(MenuItem_MouseEventListener& L);
	void HandleMouseUp(MenuItem_MouseEventListener& L);

	void Init(SceneBase* const& scene_, xx::XY const& pos, std::string_view const& txt_, float const& fontSize, std::function<void()> handler_);

	SceneBase* scene{};
	std::function<void()> handler;
	std::string txt;
	xx::XY leftBottom{}, rightTop{};	// bounding box


	bool Inside(xx::XY const& point);	// bounding box contains point?

	xx::LineStrip border;
	xx::Label content;
};

/************************************************************************/

struct Menu {
	std::vector<MenuItem> items;
	MenuItem_MouseEventListener listener;
	void Init();
	void Update();
	void Draw();
};
