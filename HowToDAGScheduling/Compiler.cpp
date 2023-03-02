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

	CompileLog grid_log = grid.compile(dag);
	CompileLog dag_log = dag.compile(grid);

	if (grid_log._success != true || dag_log._success != true)
	{
		_message.append(U"Compile Failure\n");
		if (grid_log._success != true)
			_message.append(grid_log._message);
		if (dag_log._success != true)
			_message.append(dag_log._message);

		SEManager::play(SE_name::Failure);
		_effect = FailureEffect();
	}
	else
	{
		_message.append(U"Compile Success\n");

		int response_time = 0;
		for (auto& node : dag.nodes())
			if (response_time < node.time() + node.wcet())
				response_time = node.time() + node.wcet();
		_message.append(U"Response Time: " + Format(response_time));

		DAGJsonWriter::write_result(path, grid.core_num(), response_time);

		SEManager::play(SE_name::Success);
		_effect = SuccessEffect();
	}
}

void Compiler::update()
{
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
