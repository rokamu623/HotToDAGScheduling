#pragma once
#include <Siv3D.hpp>
#include "BGMManager.h"

enum class SE_name {
	Fit, Failure, Success, Select, Cursor
};

class SEManager
{
private:
	static HashTable<SE_name, Audio> _audios;
	static bool _se_on;
	static Point _pos;

	SEManager() {};
public:
	// SEの初期化
	static void load();

	// 引数に対応したSEを鳴らす
	static void play(SE_name name);
	// GUIを表示し、SEのオンオフをコントロールする
	static void update();

	// GUIのサイズ
	static Rect UI_SIZE() { return SimpleGUI::CheckBoxRegion(U"SE", _pos).asRect(); };
};

