#include "stdafx.h"
#include "SEManager.h"

HashTable<SE_name, Audio> SEManager::_audios = {};
bool SEManager::_se_on = true;
Point SEManager::_pos = Point(0, 0);

void SEManager::load()
{
	_audios[SE_name::Fit] = Audio(U"SE/機械スイッチ.mp3");
	_audios[SE_name::Failer] = Audio(U"SE/ビープ音4.mp3");
	_audios[SE_name::Success] = Audio(U"SE/ニュースタイトル表示2.mp3");
	_audios[SE_name::Select] = Audio(U"SE/ニュースタイトル表示3.mp3");
	_audios[SE_name::Cursor] = Audio(U"SE/カーソル移動5.mp3");

	_pos = Point(Scene::Size().x - BGMManager::UI_SIZE().w - int(SEManager::UI_SIZE().w * 1.5), 0);
}

void SEManager::play(SE_name name)
{
	if(_se_on)
		_audios[name].playOneShot();
}

void SEManager::update()
{
	SimpleGUI::CheckBox(_se_on, U"SE", _pos);
}
