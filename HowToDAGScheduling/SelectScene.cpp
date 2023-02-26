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
		if (stage.clicked())
		{
			getData().path = stage.path();
			changeScene(SceneName::Main);
		}
}

void SelectScene::draw() const
{
	for (auto& stage : _stages)
		stage.draw();
}

Stage::Stage(FilePath path, Point pos)
{
	_path = path;
	_pos = pos;
	_body = Rect(pos, Point(600, 32)).asQuad();
	_name = FileSystem::BaseName(path);
	_font = Font(16);
}

bool Stage::clicked()
{
	return _body.leftClicked();
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
