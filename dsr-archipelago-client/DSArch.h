#pragma once

#include <windows.h>
#include "DSRLogger.h"
#include "DSRHook.h"

#define int3 __debugbreak();

class DSRArch {
public:
	static VOID start();
	virtual BOOL initialize();
private:
	static VOID readInput();
};