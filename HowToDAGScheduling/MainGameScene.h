#pragma once
#include <Siv3D.hpp>
#include "DAG.h"
#include "SchedGrid.h"
#include "Compiler.h"
#include "DAGJsonPackage.h"
#include "SceneName.h"
#include "BGMManager.h"
#include "SEManager.h"

class MainGameScene : public App::Scene
{
protected:
	SchedGrid _grid;
	Compiler _compiler;

	bool _compile_flag;

	DrawableText _stage_title;

	Point _home_button_pos;
	Point _compile_button_pos;

public:
	MainGameScene(const InitData& init);

	void update() override;
	void draw() const override;
};

class NormalGameScene : public MainGameScene
{
private:
	DAG _dag;
public:
	NormalGameScene(const InitData& init);

	void update() override;
	void draw() const override;
};

class RealTimeGameScene : public MainGameScene
{
private:
	DAGRealTime _dag;
public:
	RealTimeGameScene(const InitData& init);

	void update() override;
	void draw() const override;
};
