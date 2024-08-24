#pragma once
#include <vector>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <bitset>
#include <tlhelp32.h>
#include <stdio.h>
#include <functional>
#include "./submodules/minhook/include/MinHook.h"
#include "DSRLogger.h"

class DSRHook {
public:
	virtual BOOL initialize();
	virtual BYTE* findPattern(BYTE* pBaseAddress, BYTE* pbMask, const char* pszMask, size_t nLength);
	virtual BOOL enableHook();

	HANDLE hHeap;

	//0x48895C2418895424105556574154415541564157488D6C24F9
	// 48 89 5C 24 18 895424105556574154415541564157488D6C24F9
	//0x140000000

private:
	static uintptr_t GetModuleBaseAddress();

	const char* itemAob = reinterpret_cast<const char*>("\x48\x89\x5c\x24\x18\x89\x54\x24\x10\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8d\x6c\x24\xF9");
	const char* itemAobMask = "xxxxxxxxxxxxxxxxxxxxxxxxx";

	uintptr_t baseAddress = -1;
	uintptr_t giveItem = -1;
	std::shared_ptr<DSRLogger> logger;

};