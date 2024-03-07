#include "stdafx.h"
#include "CompileLog.h"

CompileLog::CompileLog(bool success, String message)
{
	this->success = success;
	this->message = message;
}
