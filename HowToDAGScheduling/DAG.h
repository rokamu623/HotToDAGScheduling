#pragma once
#include "Layout.h"
#include "Node.h"


class DAGBase
{
protected:
	Point _pos;
	Rect _graph_field;
	Rect _sched_field;
public:
	DAGBase() {};

	virtual void fit(SchedGrid& grid) {};
	virtual CompileLog compile(SchedGrid& grid) { return CompileLog(); };

	virtual void update() {};
	virtual void draw() const {};

	void draw_field() const;
};


class DAG : public DAGBase
{
private:
	Array<Node> _nodes;
public:
	DAG() {};
	DAG(Array<Node> nodes, Array<Array<int>> edges);

	void fit(SchedGrid& grid);
	CompileLog compile(SchedGrid& grid);

	void update();
	void draw() const;

	Array<Node> nodes() { return _nodes; };
};


class DAGRealTime : public DAGBase
{
private:
	Array<NodeRealTime> _nodes;
public:
	DAGRealTime() {};
	DAGRealTime(Array<NodeRealTime> nodes, Array<Array<int>> edges);

	void fit(SchedGrid& grid);
	CompileLog compile(SchedGrid& grid);

	void update();
	void draw() const;

	Array<NodeRealTime> nodes() { return _nodes; };
};
