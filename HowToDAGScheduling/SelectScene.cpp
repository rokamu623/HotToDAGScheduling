#include "stdafx.h"
#include "SelectScene.h"

SelectScene::SelectScene(const InitData& init) :IScene{ init }
{
	int i = 0;
	for (const auto& path : FileSystem::DirectoryContents(U"./", Recursive::No))
		if (FileSystem::Extension(path) == U"json")
		{
			_stages.push_back(Stage(path, Point(32, 500 - 32 * 2 * i)));
			i++;
		}
}

void SelectScene::update()
{
	for (auto& stage : _stages)
	{
		stage.update();
		if (stage.body().leftClicked())
		{
			getData().path = stage.path();
			changeScene(SceneName::Main);
			SEManager::play(SE_name::Select);
		}
	}
}

void SelectScene::draw() const
{
	SEManager::update();
	BGMManager::update();

	for (auto& stage : _stages)
		stage.draw();
}

Stage::Stage(FilePath path, Point pos)
{
	_path = path;
	_pos = pos;
	_body = Rect(pos, Point(600, 32)).asQuad();
	_name = DAGJsonReader::get_stage_name(path);
	_font = Font(16);
	_over = false;
}

Quad Stage::body()
{
	return _body;
}

void Stage::update()
{
	if (_body.mouseOver())
	{
		if (_over == false)
		{
			_over = true;
			SEManager::play(SE_name::Cursor);
		}
	}
	else
		_over = false;
}

void Stage::draw() const
{
	if (_body.mouseOver())
		_body.draw(Palette::Lightpink);
	else
		_body.draw();

	_font(_name).draw(_pos, Palette::Black);
}

FilePath Stage::path()
{
	return _path;
}
