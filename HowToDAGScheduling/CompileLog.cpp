#include "stdafx.h"
#include "CompileLog.h"

CompileLog::CompileLog(bool success, String message)
{
	_success = success;
	_message = message;
}
