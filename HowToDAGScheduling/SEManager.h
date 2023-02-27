#pragma once
#include <Siv3D.hpp>

enum class SE_name {
	Fit, Failer, Success
};

class SEManager
{
private:
	static HashTable<SE_name, Audio> _audios;

	SEManager() {};
public:
	static void load();

	static void play(SE_name name);
};

