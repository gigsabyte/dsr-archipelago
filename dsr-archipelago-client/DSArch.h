#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <bitset>
#include <tlhelp32.h>
#include <stdio.h>
#include <functional>

#include "DSRLogger.h"
#include "DSRHook.h"

#define int3 __debugbreak();


class DSRArch {
public:
	static VOID Start();
	virtual BOOL Initialize();
private:
	std::shared_ptr<DSRLogger> logger;
};