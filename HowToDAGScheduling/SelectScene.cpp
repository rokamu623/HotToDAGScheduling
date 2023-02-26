#include "stdafx.h"
#include "SelectScene.h"

SelectScene::SelectScene(const InitData& init) :IScene{ init }
{
}

void SelectScene::update()
{
	if (SimpleGUI::Button(U"Select", Vec2(600, 300)))
		changeScene(SceneName::Main);
}

void SelectScene::draw() const
{
	SimpleGUI::Button(U"Select", Vec2(600, 300));
}
