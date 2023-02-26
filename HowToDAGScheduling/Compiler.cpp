#include "stdafx.h"
#include "Compiler.h"

Compiler::Compiler()
{
	_console_field = Rect(LAYOUT::MERGIN * Point(2, 1) + LAYOUT::DAG_SPACE_SIZE * Point(1, 0), LAYOUT::CONSOLE_SPACE_SIZE);
	_font = Font(16);
}

void Compiler::compile(DAG& dag, SchedGrid& grid)
{
	CompileLog grid_log = grid.compile(dag);
	CompileLog dag_log = dag.compile(grid);
	if (grid_log._success != true || dag_log._success != true)
	{
		_message.append(U"Compile Failer\n");
		if (grid_log._success != true)
			_message.append(grid_log._message);
		if (dag_log._success != true)
			_message.append(dag_log._message);
	}
	else
		_message.append(U"Compile Success");
}

void Compiler::draw()
{
	_font(_message).draw(_console_field);
}
