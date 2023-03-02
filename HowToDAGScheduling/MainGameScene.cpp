#include "stdafx.h"
#include "MainGameScene.h"


MainGameScene::MainGameScene(const InitData& init) :IScene{ init }
{
	FilePath path = getData().path.value_or(U"DAG/sample_dag.json");
	_grid = SchedGrid(getData().core_num, ceil(DAGJsonReader::get_response_time(path) * 1.5));
	_dag = DAGJsonReader::generate_dag(path);
	_compile_flag = false;
	_stage_title = Font(24)(DAGJsonReader::get_stage_name(getData().path.value_or(U"DAG/sample_dag.json")));

	_home_button_pos = Point(SEManager::UI_SIZE().x - int(SimpleGUI::ButtonRegion(U"🏠", Point()).w * 1.5), 0);
}

void MainGameScene::update()
{
	_dag.update();
	_dag.fit(_grid);

	_compiler.update();
	if (SimpleGUI::Button(U"COMPILE", Vec2(600, 300)))
	{
		_compiler.compile(_dag, _grid);
	}

	if (SimpleGUI::Button(U"🏠", _home_button_pos))
	{
		changeScene(SceneName::Select);
		SEManager::play(SE_name::Select);
	}

	if (MouseR.down())
	{
		_compiler.compile(_dag, _grid);
	}
}

void MainGameScene::draw() const
{
	_stage_title.draw(LAYOUT::MERGIN * Point(1, 0), Palette::Black);
	SEManager::update();
	BGMManager::update();

	_dag.draw_field();
	_grid.draw_field();
	_compiler.draw_field();

	SimpleGUI::Button(U"COMPILE", Vec2(600, 300));
	SimpleGUI::Button(U"🏠", _home_button_pos);

	_dag.draw();
	_grid.draw();
	_compiler.draw();
}
