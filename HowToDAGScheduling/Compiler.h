#pragma once
#include "DAG.h"
#include "SchedGrid.h"
#include "CompileLog.h"
#include "SEManager.h"
#include "CompileEffect.h"
#include "DAGJsonPackage.h"

// DAG とプロセッサ（Grid）から結果計算（コンパイル評価）を求め、保存・エフェクト発生させる
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

	// 文字の下の台を描画
	void draw_field() const;
	void update();
	// 文字を描画
	void draw() const;
};

