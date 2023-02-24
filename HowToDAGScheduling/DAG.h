#pragma once

class Node
{
private:
	int _idx;
	int _wcet;
	Point _pos;
	Circle _body;
	Font _font;
public:
	Node() {};
	Node(int idx, int wcet, Point pos);

	void draw(Point pos);

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

