#pragma once

class Node
{
private:
	int _idx;
	int _wcet;
	Point _pos;
	Circle _body;
	Font _font;
	Array<std::reference_wrapper<Node>> _pre;
	Array<Line> _lines;
public:
	Node() {};
	Node(int idx, int wcet, Point pos);

	void append_pre(Node& pre);

	void draw(Point pos);

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

	void draw();
};

