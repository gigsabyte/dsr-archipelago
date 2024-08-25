#include "DSRHook.h"

using getItemDef = void(_fastcall*)(long long param1, uint32_t* itemData, int* param3);
getItemDef originalGetItem;

void __fastcall getItemOverride(long long param1, uint32_t* itemData, int* param3) {

	// Debug logging
	std::cout << "param1" << std::endl; 
	std::cout << param1 << std::endl;
	std::cout << "itemData" << std::endl;
	std::cout << *itemData << std::endl;
	std::cout << itemData[1] << std::endl;
	std::cout << itemData[2] << std::endl;
	std::cout << itemData[3] << std::endl;
	std::cout << "param_3" << std::endl;
	std::cout << *param3 << std::endl;
	
	// Replace the item with a prism stone if necessary
	if (param1 != 0) {
		uint32_t prism_stone = 0x40000172;
		itemData[1] = prism_stone; // item ID
		itemData[3] = 1; // amount
	}

	// Invoke the original function
	originalGetItem(param1, itemData, param3);
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

	MH_STATUS status = MH_CreateHook((LPVOID)0x1403FE3B0, &getItemOverride, (void**)&originalGetItem);
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

VOID DSRHook::giveItem(uint32_t itemId, int amount) {

	// Default to giving a prism stone
	uint32_t itemToGive = itemId;
	if (itemId == 0) {
		itemToGive = 0x40000172;
	}

	uint32_t itemData[4] = { 1, itemToGive, 0xFFFFFFFFF, amount };
	long long param1 = 0;
	int param3 = 1;

	typedef void (*GetItemFunc)(long long, uint32_t*, int*);

	GetItemFunc invokeGetItem = (GetItemFunc)0x1403FE3B0;
	invokeGetItem(param1, itemData, &param3);
}