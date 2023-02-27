#include "stdafx.h"
#include "BGMManager.h"

size_t BGMManager::_button_index = 0;
HashTable<BGM_name, Audio> BGMManager::_audios = {};
Point BGMManager::_pos = Point(0, 0);

void BGMManager::load()
{
	_audios[BGM_name::JAZZ] = Audio(Resource(U"BGM/PerituneMaterial_Conjurer_loop.mp3"));
	_audios[BGM_name::KAWAII] = Audio(Resource(U"BGM/Make-it.mp3"));

	_pos = Point(Scene::Size().x - BGMManager::UI_SIZE().w, 0);
}

void BGMManager::update()
{
	if (SimpleGUI::HorizontalRadioButtons(_button_index, { U"STOP", U"JAZZ", U"KAWAII" }, _pos))
	{
		for (auto& audio : _audios)
			audio.second.stop(1s);
		if (_button_index == 1)
		{
			_audios[BGM_name::JAZZ].play(1s);
			_audios[BGM_name::JAZZ].setVolume(0.1);
		}
		else
		{
			if (_button_index == 2)
			{
				_audios[BGM_name::KAWAII].play(1s);
				_audios[BGM_name::KAWAII].setVolume(0.1);
			}
		}
	}
}
