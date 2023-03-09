#include "stdafx.h"
#include "MainGameScene.h"


MainGameScene::MainGameScene(const InitData& init) :IScene{ init }
{
	FilePath path = getData().path.value_or(U"DAG/sample_dag.json");
	_grid = SchedGrid(getData().core_num, ceil(DAGJsonReader::get_response_time(path) * 1.5));
	_compile_flag = false;
	_stage_title = Font(24)(DAGJsonReader::get_stage_name(getData().path.value_or(U"DAG/sample_dag.json")));

	_home_button_pos = Point(SEManager::UI_SIZE().x - int(SimpleGUI::ButtonRegion(U"🏠", Point()).w * 1.5), 0);
}

void MainGameScene::update()
{
	_compiler.update();

	if (SimpleGUI::Button(U"🏠", _home_button_pos))
	{
		changeScene(SceneName::Select);
		SEManager::play(SE_name::Select);
	}

	//if (MouseR.down())
	//{
	//	_compiler.compile(_dag, _grid, getData().path.value_or(U"DAG/sample_dag.json"));
	//}
}

void MainGameScene::draw() const
{
	_stage_title.draw(LAYOUT::MERGIN * Point(1, 0), Palette::Black);
	SEManager::update();
	BGMManager::update();

	_grid.draw_field();
	_compiler.draw_field();

	SimpleGUI::Button(U"COMPILE", Vec2(600, 300));
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
	if (SimpleGUI::Button(U"COMPILE", Vec2(600, 300)))
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

ProcessorGameScene::ProcessorGameScene(const InitData& init) :MainGameScene(init)
{
	FilePath path = getData().path.value_or(U"DAG/sample_dag.json");
	_dag = DAGJsonReader::generate_dag_realtime(path);
}

void ProcessorGameScene::update()
{
	_dag.fit(_grid);
	_dag.update();
	MainGameScene::update();
	if (SimpleGUI::Button(U"COMPILE", Vec2(600, 300)))
	{
		_compiler.compile(_dag, _grid, getData().path.value_or(U"DAG/sample_dag.json"));
	}
}

void ProcessorGameScene::draw() const
{
	_dag.draw_field();
	MainGameScene::draw();
	_dag.draw();
}
