#pragma once
#include "DAG.h"
#include "SchedGrid.h"
#include "CompileLog.h"
#include "SEManager.h"
#include "CompileEffect.h"
#include "DAGJsonPackage.h"

class Compiler
{
private:
	Rect _console_field;
	Font _font;
	String _message;

	// エフェクト（Success / Failure）が発生しているときは対象のオブジェクトが入る
	Optional<CompileEffect> _effect;
public:
	Compiler();

	// コンパイル（結果計算）
	void compile(DAG& dag, SchedGrid& grid, FilePath path);
	// コンパイル（結果計算）、リアルタイムモード向け
	void compile(DAGRealTime& dag, SchedGrid& grid, FilePath path);

	void draw_field() const { _console_field.draw(LAYOUT::FIELD_COLOR); };
	void update();
	void draw() const;
};

