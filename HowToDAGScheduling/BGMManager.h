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
	static Point _pos;

	BGMManager() {};
public:
	// BGMの初期化
	static void load();
	// GUIを表示し、対応するBGMを再生
	static void update();

	//GUIのサイズ
	static Rect UI_SIZE() { return SimpleGUI::HorizontalRadioButtonsRegion({ U"STOP", U"JAZZ", U"KAWAII" }, _pos).asRect(); };
};

