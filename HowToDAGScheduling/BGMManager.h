#pragma once
#include <Siv3D.hpp>
#include "Layout.h"

enum class BGM_name {
	JAZZ, KAWAII
};

class BGMManager
{
private:
	static HashTable<BGM_name, Audio> _audios;
	static size_t _button_index;


	BGMManager() {};
public:
	static void load();
	static void update();

	static Rect UI_SIZE() { return SimpleGUI::HorizontalRadioButtonsRegion({ U"STOP", U"JAZZ", U"KAWAII" }, Point(0, 0)).asRect(); };
};

