#include "stdafx.h"
#include "ResultScene.h"

ResultDisplay::ResultDisplay(FilePath path)
{
	_field = Rect(LAYOUT::MERGIN, Scene::Size() - LAYOUT::MERGIN * 2);
	_font = Font(16);
	// DAG情報ファイルから結果テキストを読み出す
	_text = DAGJsonReader::get_result(path);
	_color = Palette::Gray;
	_color.a = 128;
}

void ResultDisplay::draw() const
{
	_field.draw(_color);
	_font(_text).draw(_field);
}


ResultStage::ResultStage(FilePath path, Point pos)
{
	_path = path;
	_pos = pos;
	_body = Quad(pos + Point(-32, 0), pos + Point(0, 32), pos + Point(600, 32), pos + Point(600 - 32, 0));
	// ステーの名前をDAG情報ファイルから取得
	_name = DAGJsonReader::get_stage_name(path);
	_font = Font(16);
	_over = false;
}

void ResultStage::update()
{
	// マウスが上に乗っているとき
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

void ResultStage::draw() const
{
	_body.movedBy(4, 4).draw();
	if (_over)
		_body.draw(Palette::Lightpink);
	else
		_body.draw(Palette::Black);

	_font(_name).draw(_pos);
}


ResultScene::ResultScene(const InitData& init) :IScene{ init }
{
	int i = 0;
	// DAG下のDAG情報jsonファイルをロードし、各jsonファイルに対し選択肢を作成
	for (const auto& path : FileSystem::DirectoryContents(U"./DAG/", Recursive::No))
		if (FileSystem::Extension(path) == U"json")
		{
			_stages.push_back(ResultStage(path, Point(64, 500 - 32 * 2 * i)));
			i++;
		}
	_select_button_pos = Point(SEManager::UI_SIZE().x - int(SimpleGUI::ButtonRegion(U"Result", Point()).w * 1.5), 0);
	_display = none;
}

void ResultScene::update()
{
	if (_display.has_value() == true)
	{
		// リザルト表示されているときにクリックされたら表示を消す
		if (MouseL.down() && BGMManager::UI_SIZE().leftClicked() != true && SEManager::UI_SIZE().leftClicked() != true)
			_display = none;
	}
	else
	{
		// リザルト表示がされていないとき
		for (auto& stage : _stages)
		{
			stage.update();
			// あるステージが選択されたらその結果を表示
			if (stage.body().leftClicked())
				_display = ResultDisplay(stage.path());
		}
		// Select がクリックされたらステージセレクトに戻る
		if (SimpleGUI::Button(U"Select", _select_button_pos))
		{
			changeScene(SceneName::Select);
			SEManager::play(SE_name::Select);
		}
	}
}

void ResultScene::draw() const
{
	SEManager::update();
	BGMManager::update();

	for (auto& stage : _stages)
		stage.draw();
	SimpleGUI::Button(U"Select", _select_button_pos);

	// 表示ができるときはする
	if (_display.has_value())
		_display.value().draw();
}
