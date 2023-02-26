#include "stdafx.h"
#include "Compiler.h"

Compiler::Compiler()
{
	_console_field = Rect(LAYOUT::MERGIN * Point(2, 1) + LAYOUT::DAG_SPACE_SIZE * Point(1, 0), LAYOUT::CONSOLE_SPACE_SIZE);
}

void Compiler::compile(DAG& dag, SchedGrid& grid)
{
	ClearPrint();
	CompileLog grid_log = grid.compile(dag);
	CompileLog dag_log = dag.compile(grid);
	if (grid_log._success != true || dag_log._success != true)
	{
		Print << U"Compile Failer";
		if (grid_log._success != true)
			Print << grid_log._message;
		if (dag_log._success != true)
			Print << dag_log._message;
	}
	else
		Print << U"Compile Success";
}

void Compiler::draw()
{
}
