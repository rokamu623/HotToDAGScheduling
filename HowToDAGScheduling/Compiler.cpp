#include "stdafx.h"
#include "Compiler.h"

Compiler::Compiler()
{
	_console_field = Rect(LAYOUT::MERGIN * Point(2, 1) + LAYOUT::DAG_SPACE_SIZE * Point(1, 0) + Point(0, LAYOUT::STAZE_SPACE_HEIGHT), LAYOUT::CONSOLE_SPACE_SIZE);
	_font = Font(16);

	_effect = none;
}

void Compiler::compile(DAG& dag, SchedGrid& grid, FilePath path)
{
	_message.clear();

	// プロセッサ（グリッド）の結果取得
	CompileLog grid_log = grid.compile(dag);
	// DAGの結果取得
	CompileLog dag_log = dag.compile(grid);

	// 両方成功していたら成功
	if (grid_log.success == true && dag_log.success == true)
	{
		_message.append(U"Compile Success\n");

		// 応答時間を計算（最も大きなノードの終了時間）
		int response_time = 0;
		for (auto& node : dag.nodes())
			if (response_time < node.finish_time())
				response_time = node.finish_time();
		_message.append(U"Response Time: " + Format(response_time));

		// DAG情報ファイルに書き込み
		DAGJsonWriter::write_result(path, grid.core_num(), response_time);

		SEManager::play(SE_name::Success);
		_effect = SuccessEffect();
	}
	// 失敗した場合
	else
	{
		_message.append(U"Compile Failure\n");

		// プロセッサ（グリッド）の失敗原因ログを保存
		if (grid_log.success != true)
			_message.append(grid_log.message);
		// DAGの失敗原因ログを保存
		if (dag_log.success != true)
			_message.append(dag_log.message);

		SEManager::play(SE_name::Failure);
		_effect = FailureEffect();
	}
}

void Compiler::compile(DAGRealTime& dag, SchedGrid& grid, FilePath path)
{
	_message.clear();

	// プロセッサ（グリッド）の結果取得
	CompileLog grid_log = grid.compile(dag);
	// DAGの結果取得
	CompileLog dag_log = dag.compile(grid);

	// 両方成功していたら成功
	if (grid_log.success == true && dag_log.success == true)
	{
		_message.append(U"Compile Success\n");

		// 応答時間を計算（最も大きなノードの終了時間）
		int response_time = 0;
		for (auto& node : dag.nodes())
			if (response_time < node.finish_time())
				response_time = node.finish_time();
		_message.append(U"Response Time: " + Format(response_time));

		// DAG情報ファイルに書き込み
		DAGJsonWriter::write_result(path, grid.core_num(), response_time);

		SEManager::play(SE_name::Success);
		_effect = SuccessEffect();
	}
	// 失敗した場合
	else
	{
		_message.append(U"Compile Failure\n");

		// プロセッサ（グリッド）の失敗原因ログを保存
		if (grid_log.success != true)
			_message.append(grid_log.message);
		// DAGの失敗原因ログを保存
		if (dag_log.success != true)
			_message.append(dag_log.message);

		SEManager::play(SE_name::Failure);
		_effect = FailureEffect();
	}
}

void Compiler::draw_field() const
{
	_console_field.draw(LAYOUT::FIELD_COLOR);
}

void Compiler::update()
{
	// エフェクトがあるならそれを更新
	if (_effect.has_value())
	{
		_effect.value().update();
		if (_effect.value().finish())
			_effect = none;
	}
}

void Compiler::draw() const
{
	_font(_message).draw(_console_field);

	if (_effect.has_value())
		_effect.value().draw();
}
