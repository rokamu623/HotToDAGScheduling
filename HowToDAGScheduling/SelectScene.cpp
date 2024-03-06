#include "stdafx.h"
#include "SelectScene.h"

SelectScene::SelectScene(const InitData& init) :IScene{ init }
{
	int i = 0;
	// DAG下のDAG情報jsonファイルをロードし、各jsonファイルに対し選択肢を作成
	for (const auto& path : FileSystem::DirectoryContents(U"./DAG/", Recursive::No))
		if (FileSystem::Extension(path) == U"json")
		{
			_stages.push_back(Stage(path, Point(64, 500 - 32 * 2 * i)));
			i++;
		}

	_real_time_mode = false;

	_result_button_pos = Point(SEManager::UI_SIZE().x - int(SimpleGUI::ButtonRegion(U"Result", Point()).w * 1.5), 0);
	_real_time_pos = Point(0, 0);
}

void SelectScene::update()
{
	for (auto& stage : _stages)
	{
		stage.update();
		// ステージがクリックされたら
		if (stage.body().leftClicked())
		{
			// DAG情報ファイルのパスとコア数を保存してメインゲームへ
			getData().path = stage.path();
			getData().core_num = stage.core_num();
			if (_real_time_mode)
				changeScene(SceneName::RealTime);
			else
				changeScene(SceneName::Main);
			SEManager::play(SE_name::Select);
		}
	}

	// Result ボタンが押されたらリザルトシーンへ
	if (SimpleGUI::Button(U"Result", _result_button_pos))
	{
		changeScene(SceneName::Result);
		SEManager::play(SE_name::Select);
	}

	// Real Time ボタンが押されたらリアルタイムモードへ
	if (SimpleGUI::CheckBox(_real_time_mode, U"Real Time", _real_time_pos))
		SEManager::play(SE_name::Select);
}

void SelectScene::draw() const
{
	SEManager::update();
	BGMManager::update();

	for (auto& stage : _stages)
		stage.draw();

	SimpleGUI::Button(U"Result", _result_button_pos);

	bool tmp = _real_time_mode;
	SimpleGUI::CheckBox(tmp, U"Real Time", _real_time_pos);
}

Stage::Stage(FilePath path, Point pos)
{
	_path = path;
	_pos = pos;
	_body = Quad(pos, pos + Point(-32, 32), pos + Point(600 - 32, 32), pos + Point(600, 0));
	_name = DAGJsonReader::get_stage_name(path);
	_font = Font(16);
	_over = false;
	_core_num = DAGJsonReader::get_core_num(path);
	_scroll = _core_num;

	Point tri_pos = _font(_name + U"   " + Format(_core_num) + U" core").region(_pos).rightCenter().asPoint();
	_up_tri = Triangle(Point(0, 0), Point(-8, 8), Point(8, 8));
	_up_tri.setCentroid(tri_pos + Point(-32, -16 + 4));
	_down_tri = Triangle(Point(0, 0), Point(-8, -8), Point(8, -8));
	_down_tri.setCentroid(tri_pos + Point(-32, 16 + 4));
}

Quad Stage::body()
{
	return _body;
}

void Stage::update()
{
	if (_body.mouseOver())
	{
		if (Mouse::Wheel() > 0 && _scroll > 1)
		{
			_scroll -= 1;
			_core_num -= 1;
		}
		if (Mouse::Wheel() < 0 && _scroll < 10)
		{
			_scroll += 1;
			_core_num += 1;
		}
		if (MouseM.down())
		{
			_core_num = DAGJsonReader::get_core_num(_path);
			_scroll = _core_num;
		}

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
	_body.movedBy(4, 4).draw(Palette::Black);
	if (_body.mouseOver())
		_body.draw(Palette::Lightpink);
	else
		_body.draw();

	_font(_name+U"   "+Format(_core_num)+U" core").draw(_pos, Palette::Black);

	_up_tri.drawFrame().draw(Palette::Black);
	_down_tri.drawFrame().draw(Palette::Black);
}

FilePath Stage::path()
{
	return _path;
}
