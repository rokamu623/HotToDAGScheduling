#pragma once
#include <Siv3D.hpp>
#include "SceneName.h"
#include "BGMManager.h"
#include "SEManager.h"
#include "DAGJsonReader.h"
#include "SEManager.h"

class Stage
{
private:
	FilePath _path;
	Point _pos;
	Quad _body;
	String _name;
	Font _font;
	bool _over;

public:
	Stage() {};
	Stage(FilePath path, Point pos);

	Quad body();
	void update();
	void draw() const;

	FilePath path();
};

class SelectScene :public App::Scene
{
private:
	Array<Stage> _stages;
public:
	SelectScene(const InitData& init);

	void update() override;
	void draw() const override;
};

