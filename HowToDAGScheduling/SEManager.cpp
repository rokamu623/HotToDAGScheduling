#include "stdafx.h"
#include "SEManager.h"

HashTable<SE_name, Audio> SEManager::_audios = {};
bool SEManager::_se_on = true;
Point SEManager::_pos = Point(0, 0);

void SEManager::load()
{
	_audios[SE_name::Fit] = Audio(Resource(U"SE/fit.mp3"));
	_audios[SE_name::Failer] = Audio(Resource(U"SE/failer.mp3"));
	_audios[SE_name::Success] = Audio(Resource(U"SE/success.mp3"));
	_audios[SE_name::Select] = Audio(Resource(U"SE/select.mp3"));
	_audios[SE_name::Cursor] = Audio(Resource(U"SE/cursor.mp3"));

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
