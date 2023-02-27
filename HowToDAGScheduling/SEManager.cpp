#include "stdafx.h"
#include "SEManager.h"

HashTable<SE_name, Audio> SEManager::_audios = {};

void SEManager::load()
{
	_audios[SE_name::Fit] = Audio(U"SE/機械スイッチ.mp3");
	_audios[SE_name::Failer] = Audio(U"SE/ビープ音4.mp3");
	_audios[SE_name::Success] = Audio(U"SE/ニュースタイトル表示2.mp3");
}

void SEManager::play(SE_name name)
{
	_audios[name].playOneShot();
}
