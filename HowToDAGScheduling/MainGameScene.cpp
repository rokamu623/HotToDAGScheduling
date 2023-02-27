#include "stdafx.h"
#include "MainGameScene.h"


MainGameScene::MainGameScene(const InitData& init) :IScene{ init }
{
	dag = DAGJsonReader::generate_dag(getData().path.value_or(U"sample_dag.json"));
	_compile_flag = false;
	_stage_title = Font(24)(DAGJsonReader::get_stage_name(getData().path.value_or(U"sample_dag.json")));
}

void MainGameScene::update()
{
	dag.update();
	if (MouseL.up())
		dag.fit(grid);

	if (SimpleGUI::Button(U"COMPILE", Vec2(600, 300)))
	{
		compiler.compile(dag, grid);
	}

	if (MouseR.down())
	{
		compiler.compile(dag, grid);
	}
}

void MainGameScene::draw() const
{
	_stage_title.draw(LAYOUT::MERGIN * Point(1, 0), Palette::Black);
	SEManager::update();
	BGMManager::update();

	dag.draw_field();
	grid.draw_field();
	compiler.draw_field();

	SimpleGUI::Button(U"COMPILE", Vec2(600, 300));

	dag.draw();
	grid.draw();
	compiler.draw();
}
