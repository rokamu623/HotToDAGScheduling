#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene(const InitData& init) :IScene{ init }
{
	_title_font = Font(64);
	_small_font = Font(32);
}

void TitleScene::update()
{

	if (Scene::Rect().leftClicked() && BGMManager::UI_SIZE().leftClicked() != true)
		changeScene(SceneName::Select);
}

void TitleScene::draw() const
{
	BGMManager::update();

	_title_font(U"How To DAG Scheduling ?").drawAt(Scene::Center().movedBy(Point(0, -64)));

	_small_font(U"Click Anywhere").drawAt(Scene::Center().movedBy(Point(0, 64)));
}
