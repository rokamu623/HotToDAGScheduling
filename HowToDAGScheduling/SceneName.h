#pragma once

enum class SceneName
{
	Title, Select, Main
};

struct GameData
{
	Optional<FilePath> path = none;
};

using App = SceneManager<SceneName, GameData>;
