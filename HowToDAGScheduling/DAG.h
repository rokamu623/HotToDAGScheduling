#pragma once

class Node
{
private:
	int _idx;
	int _wcet;
	bool _chase;
	Point _pos;
	Circle _graph_body;
	Rect _sched_body;
	Font _font;
	Array<std::reference_wrapper<Node>> _pre;
	Array<Line> _lines;
public:
	Node() {};
	Node(int idx, int wcet, Point pos);

	void append_pre(Node& pre);

	bool update();
	void draw_sched();
	void draw_graph(Point pos);

	int idx();
	Point pos();
};

class DAG
{
private:
	Array<Node> _nodes;
	Point _pos;
public:
	DAG() {};
	DAG(Array<Node> nodes, Array<Array<int>> edges, Point pos);

	void update();
	void draw();
};

