#pragma once
#include <Siv3D.hpp>
#include "SceneName.h"

class SelectScene :public App::Scene
{
public:
	SelectScene(const InitData& init);

	void update() override;
	void draw() const override;
};

