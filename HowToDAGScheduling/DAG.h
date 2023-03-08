#pragma once
#include "CompileLog.h"
#include "Layout.h"
#include "SEManager.h"

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

	bool _visible;
public:
	Node() {};
	Node(int idx, int wcet, Point pos, bool real_time_mode);

	void append_pre(Node& pre);
	void fit(SchedGrid& grid);

	void set_color(Color color) { _color = color; };
	void set_sched_pos(Point pos) { _sched_body.setPos(pos); };

	CompileLog compile();
	void assign(int time, int core);

	void real_time_ready();

	bool update();
	void draw_sched() const;
	void draw_graph(Point pos) const;

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
	Rect _graph_field;
	Rect _sched_field;
public:
	DAG() {};
	DAG(Array<Node> nodes, Array<Array<int>> edges, bool real_time_mode);

	void fit(SchedGrid& grid);
	CompileLog compile(SchedGrid& grid);

	void update();
	void draw() const;

	void draw_field() const;

	Array<Node> nodes() { return _nodes; };
};

