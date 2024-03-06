#include "stdafx.h"
#include "MainGameScene.h"


MainGameScene::MainGameScene(const InitData& init) :IScene{ init }
{
	// Select Scene で保存したデータDAG情報ファイルのパスを読み出し
	FilePath path = getData().path.value_or(U"DAG/sample_dag.json");
	// スケジューリングのコアの枠を作る、縦長: コア数、横長: 応答時間 * 1.5
	_grid = SchedGrid(getData().core_num, ceil(DAGJsonReader::get_response_time(path) * 1.5));
	_compile_flag = false;
	_stage_title = Font(24)(DAGJsonReader::get_stage_name(path));

	_home_button_pos = Point(SEManager::UI_SIZE().x - int(SimpleGUI::ButtonRegion(U"🏠", Point()).w * 1.5), 0);
	_compile_button_pos = LAYOUT::MERGIN * 2 + Point(LAYOUT::SCHED_SPACE_SIZE.x, LAYOUT::DAG_SPACE_SIZE.y) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT) +
		LAYOUT::SPACE_SPACE_SIZE * Point(1, 0) - SimpleGUI::ButtonRegion(U"COMPILE", Point()).size.asPoint() * Point(1, 0);
}

void MainGameScene::update()
{
	_compiler.update();

	// ホーム ボタンが押されたら Select Scene に戻る
	if (SimpleGUI::Button(U"🏠", _home_button_pos))
	{
		changeScene(SceneName::Select);
		SEManager::play(SE_name::Select);
	}
}

void MainGameScene::draw() const
{
	_stage_title.draw(LAYOUT::MERGIN * Point(1, 0), Palette::Black);
	SEManager::update();
	BGMManager::update();

	_grid.draw_field();
	_compiler.draw_field();

	SimpleGUI::Button(U"COMPILE", _compile_button_pos);
	SimpleGUI::Button(U"🏠", _home_button_pos);

	_grid.draw();
	_compiler.draw();
}


NormalGameScene::NormalGameScene(const InitData& init) :MainGameScene(init)
{
	FilePath path = getData().path.value_or(U"DAG/sample_dag.json");
	_dag = DAGJsonReader::generate_dag(path);
}

void NormalGameScene::update()
{
	_dag.fit(_grid);
	_dag.update();
	MainGameScene::update();
	// コンパイル ボタンが押されたらコンパイルを実行
	if (SimpleGUI::Button(U"COMPILE", _compile_button_pos))
	{
		_compiler.compile(_dag, _grid, getData().path.value_or(U"DAG/sample_dag.json"));
	}
}

void NormalGameScene::draw() const
{
	_dag.draw_field();
	MainGameScene::draw();
	_dag.draw();
}


RealTimeGameScene::RealTimeGameScene(const InitData& init) :MainGameScene(init)
{
	FilePath path = getData().path.value_or(U"DAG/sample_dag.json");
	_dag = DAGJsonReader::generate_dag_realtime(path);
}

void RealTimeGameScene::update()
{
	_dag.fit(_grid);
	_dag.update();
	MainGameScene::update();
	// コンパイル ボタンが押されたらコンパイルを実行
	if (SimpleGUI::Button(U"COMPILE", _compile_button_pos))
	{
		_compiler.compile(_dag, _grid, getData().path.value_or(U"DAG/sample_dag.json"));
	}
}

void RealTimeGameScene::draw() const
{
	_dag.draw_field();
	MainGameScene::draw();
	_dag.draw();
}
