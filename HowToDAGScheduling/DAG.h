#pragma once
#include "CompileLog.h"
#include "Layout.h"
#include "SEManager.h"

class SchedGrid;

// ノードの基底クラス
class NodeBase
{
protected:
	int _idx;
	int _wcet;
	int _start_time;
	int _core;
	Array<std::reference_wrapper<NodeBase>> _pre;

	// DAGグラフ（左上）でのノード
	Point _graph_pos;
	// 実際に並べる長方形
	Circle _graph_body;
	Color _color;
	Array<Line> _lines;
	Font _font;

	Rect _sched_body;
	bool _chase;
public:
	NodeBase() {};
	NodeBase(int idx, int wcet, Point pos);

	// 前任者を追加（エッジの登録）
	void append_pre(NodeBase& pre);
	// その瞬間に触れているグリッドに長方形を合わせる
	void fit(SchedGrid& grid);

	void set_color(Color color) { _color = color; };
	void set_sched_pos(Point pos) { _sched_body.setPos(pos); };

	// コンパイル（結果計算）
	CompileLog compile();
	virtual void real_time_ready() {};

	virtual bool update();
	// スケジュール配置用の長方形の描画
	virtual void draw_sched() const;
	// DAG 本体の描画
	void draw_graph(Point pos) const;

	int idx() { return _idx; };
	int finish_time() { return _start_time + _wcet; };
	int start_time() { return _start_time; };
	int core() { return _core; };
	Point graph_pos() { return _graph_pos; };
	Rect sched_body() { return _sched_body; };
};



// 通常モードのノード、NodeBase と全く同じ
class Node : public NodeBase
{
public:
	Node() {};
	Node(int idx, int wcet, Point pos);
};


// リアルタイムモードのノード
class NodeRealTime : public NodeBase
{
private:
	bool _visible;

public:
	NodeRealTime() {};
	NodeRealTime(int idx, int wcet, Point pos);

	void real_time_ready() override;

	bool update() override;
	void draw_sched() const override;
};

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
