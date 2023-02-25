#pragma once
#include "CompileLog.h"

class SchedGrid;

class Node
{
private:
	int _idx;
	int _wcet;
	int _time;
	int _core;
	Array<std::reference_wrapper<Node>> _pre;

	Point _graph_pos;
	Circle _graph_body;
	Color _color;
	Array<Line> _lines;
	Font _font;

	Rect _sched_body;
	bool _chase;
public:
	Node() {};
	Node(int idx, int wcet, Point pos);

	void append_pre(Node& pre);
	void fit(Point pos);

	void set_color(Color color) { _color = color; };

	CompileLog compile();
	void assign(int time, int core);

	bool update();
	void draw_sched();
	void draw_graph(Point pos);

	int idx();
	int wcet() { return _wcet; };
	int time() { return _time; };
	int core() { return _core; };
	Point graph_pos();
	Rect sched_body() { return _sched_body; };
};

class DAG
{
private:
	Array<Node> _nodes;
	Point _pos;
public:
	DAG() {};
	DAG(Array<Node> nodes, Array<Array<int>> edges, Point pos);

	void fit(SchedGrid& grid);
	CompileLog compile(SchedGrid& grid);

	void update();
	void draw();

	Array<Node> nodes() { return _nodes; };
};

