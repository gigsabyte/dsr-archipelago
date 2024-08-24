#include "DSRHook.h"

using getItemDef = int(_fastcall*)(int param_1, uint32_t param_2, int param_3, int param_4);
getItemDef originalGetItem;

// 3 humanity:
// 1073741824 dec = 40000000 hex. param_1 = item category
// 500 dec = 1F4 hex. param_2 = item id (offset)
// 3 = amount
// -1 = param_4 = used as a parameter for another function IF value is NOT -1
int __fastcall getItemOverride(int param_1, uint32_t param_2, int param_3, int param_4) {
	std::cout << param_1 << std::endl;
	std::cout << param_2 << std::endl;
	std::cout << param_3 << std::endl;
	std::cout << param_4 << std::endl;
	
	int prism_stone_category = 0x40000000;
	uint32_t prism_stone_id = 0x0172;
	return originalGetItem(prism_stone_category, prism_stone_id, 1, param_4);
}

/*
* Check if a basic hook is working on this version of the game
*/
BOOL DSRHook::initialize() {
	logger = DSRLogger::get();
	logger->log("DSRHook::initialize()");

	try {
		if (MH_Initialize() != MH_OK) return false;
	}
	catch (const std::exception&) {
		logger->log("Cannot initialize MinHook");
		return false;
	}

	baseAddress = GetModuleBaseAddress();

	if (baseAddress < 0) {
		logger->log("Couldn't find module base address");
		return false;
	}

	int executableSize = 49108 * 1024;
	giveItem = reinterpret_cast<uintptr_t>(findPattern((BYTE*)baseAddress, (BYTE*)itemAob, itemAobMask, executableSize));

	if (giveItem < 0) {
		logger->log("Couldn't find give item address with base address \'" + std::to_string(baseAddress) + "\' and itemAob " + itemAob);
		return false;
	}
	else {
		logger->log("Found give item address at \'" + std::to_string(giveItem) + "\'");
	}

	MH_STATUS status = MH_CreateHook((LPVOID)0x1403F8780, &getItemOverride, (void**)&originalGetItem);
	if (status != MH_OK) {
		logger->log("Couldn't create hook!");
		return false;
	}
	logger->log("Created hook!");
	return true;
}

BOOL DSRHook::enableHook() {
	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		logger->log("Couldn't enable hook!");
		return false;
	}
	logger->log("Hooked successfully!");
	return true;
}

uintptr_t DSRHook::GetModuleBaseAddress() {
	const char* lpModuleName = "DarkSoulsRemastered.exe";
	DWORD procId = GetCurrentProcessId();

	MODULEENTRY32 lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procId);
	if (!hSnapShot)
		return NULL;
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);
	while (bModule)
	{
		if (!strcmp(lpModuleEntry.szModule, lpModuleName))
		{
			CloseHandle(hSnapShot);
			return (uintptr_t)lpModuleEntry.modBaseAddr;
		}
		bModule = Module32Next(hSnapShot, &lpModuleEntry);
	}
	CloseHandle(hSnapShot);
	return NULL;
}

// From https://github.com/learn-more/findpattern-bench/blob/master/patterns/superdoc1234.h
BYTE* DSRHook::findPattern(BYTE* pBaseAddress, BYTE* pbMask, const char* pszMask, size_t nLength) {
	auto DataCompare = [](const BYTE* pData, const BYTE* mask, const char* cmask, BYTE chLast, size_t iEnd) -> bool {
		if (pData[iEnd] != chLast) return false;
		for (; *cmask; ++cmask, ++pData, ++mask) {
			if (*cmask == 'x' && *pData != *mask) {
				return false;
			}
		}

		return true;
	};

	auto iEnd = strlen(pszMask) - 1;
	auto chLast = pbMask[iEnd];

	auto* pEnd = pBaseAddress + nLength - strlen(pszMask);
	for (; pBaseAddress < pEnd; ++pBaseAddress) {
		if (DataCompare(pBaseAddress, pbMask, pszMask, chLast, iEnd)) {
			return pBaseAddress;
		}
	}

	return nullptr;
}