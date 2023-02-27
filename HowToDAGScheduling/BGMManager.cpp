#include "stdafx.h"
#include "BGMManager.h"

BGMManager::BGMManager()
{
	_audios.push_back(Audio());
	_audios.push_back(Audio(U"BGM/PerituneMaterial_Conjurer_loop.mp3"));
	_audios.push_back(Audio(U"BGM/Make-it.mp3"));
	_button_index = 0;
}

void BGMManager::update()
{
	if (SimpleGUI::HorizontalRadioButtons(_button_index, { U"STOP", U"JAZZ", U"KAWAII" }, Point(0, 0)))
	{
		for (auto& audio : _audios)
			audio.stop(1s);
		if (_button_index < _audios.size() && _audios[_button_index].isEmpty() != true)
		{
			_audios[_button_index].play(1s);
			_audios[_button_index].setVolume(0.1);
		}
	}
}
