#pragma once
#include <Siv3D.hpp>
#include "Layout.h"

class BGMManager
{
	Array<Audio> _audios;
	size_t _button_index;
public:
	BGMManager();

	void update();

	static Rect UI_SIZE() { return SimpleGUI::HorizontalRadioButtonsRegion({ U"STOP", U"JAZZ", U"KAWAII" }, Point(0, 0)).asRect(); };
};

