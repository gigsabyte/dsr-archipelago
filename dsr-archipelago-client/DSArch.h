#pragma once

#include <windows.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <bitset>
#include <tlhelp32.h>
#include <stdio.h>
#include <functional>

#define int3 __debugbreak();


class DSRArch {
public:
	static VOID Start();
	virtual BOOL Initialize();
};