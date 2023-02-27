#pragma once
#include <Siv3D.hpp>
#include "SceneName.h"
#include "BGMManager.h"
#include "SEManager.h"

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

