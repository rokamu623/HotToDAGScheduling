#include "stdafx.h"
#include "Compiler.h"

void Compiler::compile(DAG& dag, SchedGrid& grid)
{
	ClearPrint();
	CompileLog grid_log = grid.compile(dag);
	CompileLog dag_log = dag.compile(grid);
	if (grid_log._success != true || dag_log._success != true)
		Print << U"Compile Error";
	if (grid_log._success != true)
		Print << grid_log._message;
	if (dag_log._success != true)
		Print << dag_log._message;
}
