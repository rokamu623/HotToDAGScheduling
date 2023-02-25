#pragma once
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
	Cell(Point pos);

	bool invalid();
	void assign(bool input);

	void draw();

	int core() { return _core; };
	int time() { return _time; };
	Rect body() { return _body; };
};

class SchedGrid
{
private:
	Grid<Cell> _cells;

public:
	SchedGrid();

	void compile(DAG dag);

	void draw();

	Grid<Cell> cells();
};

