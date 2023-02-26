#pragma once
#include <Siv3D.hpp>
#include "SceneName.h"

class TitleScene :public App::Scene
{
private:
	Font _title_font;
	Font _small_font;
public:
	TitleScene(const InitData& init);

	void update() override;
	void draw() const override;
};

