#pragma once
#include <Siv3D.hpp>
#include "BGMManager.h"

enum class SE_name {
	Fit, Failer, Success, Select, Cursor
};

class SEManager
{
private:
	static HashTable<SE_name, Audio> _audios;
	static bool _se_on;
	static Point _pos;

	SEManager() {};
public:
	static void load();

	static void play(SE_name name);
	static void update();

	static Rect UI_SIZE() { return SimpleGUI::CheckBoxRegion(U"SE", _pos).asRect(); };
};

