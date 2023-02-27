#pragma once
#include "DAG.h"
#include "SchedGrid.h"
#include "CompileLog.h"
#include "SEManager.h"

class Compiler
{
private:
	Rect _console_field;
	Font _font;
	String _message;
public:
	Compiler();

	void compile(DAG& dag, SchedGrid& grid);

	void draw_field() const { _console_field.draw(LAYOUT::FIELD_COLOR); };
	void draw() const;
};

