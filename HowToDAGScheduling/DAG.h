#pragma once
#include "Layout.h"
#include "Node.h"

// DAGの基底クラス
class DAGBase
{
protected:
	Point _pos;
	// DAG 表示位置の下地
	Rect _graph_field;
	// スケジューリング長方形が最初に置いてあるエリアの下地
	Rect _sched_field;
public:
	DAGBase() {};

	// ドラッグ終了したときにスケジューリング長方形をグリッドに合わせる
	virtual void fit(SchedGrid& grid) {};
	// コンパイル（結果計算）
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

	// ドラッグ終了したときにスケジューリング長方形をグリッドに合わせる
	void fit(SchedGrid& grid);
	// コンパイル（結果計算）
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

	// ドラッグ終了したときにスケジューリング長方形をグリッドに合わせる
	void fit(SchedGrid& grid);
	// コンパイル（結果計算）
	CompileLog compile(SchedGrid& grid);

	void update();
	void draw() const;

	Array<NodeRealTime> nodes() { return _nodes; };
};
