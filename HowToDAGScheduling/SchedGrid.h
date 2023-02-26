#pragma once
#include "CompileLog.h"
#include "Layout.h"

class DAG;

class Cell
{
private:
	int _core;
	int _time;

	Rect _body;
	bool _invalid;
	bool _assigned;

public:
	Cell() {};
	Cell(Point pos, Point offset);

	bool invalid();
	void assign(bool input);

	void draw() const;

	int core() { return _core; };
	int time() { return _time; };
	Rect body() { return _body; };
};

class SchedGrid
{
private:
	Grid<Cell> _cells;
	Rect _field;
	Point _grid_pos;

public:
	SchedGrid();

	CompileLog compile(DAG dag);

	void draw() const;
	void draw_field() const { _field.draw(LAYOUT::FIELD_COLOR); };

	Grid<Cell> cells();
};

