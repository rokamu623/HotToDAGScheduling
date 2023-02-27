#include "stdafx.h"
#include "MainGameScene.h"


MainGameScene::MainGameScene(const InitData& init) :IScene{ init }
{
	dag = DAGJsonReader::generate_dag(getData().path.value_or(U"sample_dag.json"));
	_compile_flag = false;
	//Scene::SetBackground(Palette::Orange);
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
	BGMManager::update();

	dag.draw_field();
	grid.draw_field();
	compiler.draw_field();

	SimpleGUI::Button(U"COMPILE", Vec2(600, 300));

	dag.draw();
	grid.draw();
	compiler.draw();
}
