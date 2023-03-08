#pragma once
#include <Siv3D.hpp>
#include "SceneName.h"
#include "BGMManager.h"
#include "SEManager.h"
#include "DAGJsonPackage.h"
#include "SEManager.h"

class Stage
{
private:
	FilePath _path;
	String _name;
	int _core_num;

	Point _pos;
	Quad _body;
	bool _over;
	Font _font;
	int _scroll;

	Triangle _up_tri;
	Triangle _down_tri;

public:
	Stage() {};
	Stage(FilePath path, Point pos);

	Quad body();
	void update();
	void draw() const;

	FilePath path();
	int core_num(){ return _core_num; };
};

class SelectScene :public App::Scene
{
private:
	Array<Stage> _stages;

	Point _result_button_pos;
	Point _real_time_pos;

	bool _real_time_mode;
public:
	SelectScene(const InitData& init);

	void update() override;
	void draw() const override;
};

