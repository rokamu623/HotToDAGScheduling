#pragma once
#include "DAG.h"
#include "SchedGrid.h"
#include "CompileLog.h"

class Compiler
{
public:
	Compiler() {};

	void compile(DAG& dag, SchedGrid& grid);
};

