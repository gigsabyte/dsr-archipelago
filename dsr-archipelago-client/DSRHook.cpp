#include "DSRHook.h"

extern DSRLogger* Logger;

using getItemDef = void(_fastcall*)(long long param1, uint32_t* itemData, int* param3);
getItemDef originalGetItem;

void __fastcall getItemOverride(long long param1, uint32_t* itemData, int* param3) {

#if _DEBUG
	// Debug logging
	Logger->log("\nReceiving item...");
	Logger->log("itemData: [ ", *itemData, ", ", itemData[1], ", ", itemData[2], ", ", itemData[3], "]");
	Logger->log("param3: [ ", *param3, ", ", param3[1], "]");
	Logger->log("End Item\n");
#endif

	// Invoke the original function
	originalGetItem(param1, itemData, param3);
}


using setEventFlagDef = int(_fastcall*)(uint32_t* param1, int param2, uint32_t value);
setEventFlagDef originalSetEventFlag;

int __fastcall setEventFlagOverride(uint32_t* param1, int id, uint32_t value) {
	Logger->debug("Event! ID: [", id, "]", " Value: [", value, "]");
	return originalSetEventFlag(param1, id, value);
}

/*
* Check if a basic hook is working on this version of the game
*/
BOOL DSRHook::initialize() {
	Logger->debug("Initializing MinHook!");

	try {
		if (MH_Initialize() != MH_OK) return false;
	}
	catch (const std::exception&) {
		Logger->error("Cannot initialize MinHook");
		return false;
	}

	MH_STATUS status = MH_CreateHook((LPVOID)0x1403FE3B0, &getItemOverride, (void**)&originalGetItem);
	if (status != MH_OK) {
		Logger->error("Couldn't create hook for getItem!");
		return false;
	}
	status = MH_CreateHook((LPVOID)0x1404F5780, &setEventFlagOverride, (void**)&originalSetEventFlag);
	if (status != MH_OK) {
		Logger->error("Couldn't create hook for setEventFlag!");
		return false;
	}
	Logger->debug("Created hooks!");
	return true;
}

BOOL DSRHook::enableHook() {
	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		Logger->error("Couldn't enable hook!");
		return false;
	}
	Logger->log("Hooked successfully!");
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
	int param3[2] = {1, -1};

	typedef void (*GetItemFunc)(long long, uint32_t*, int*);

	GetItemFunc invokeGetItem = (GetItemFunc)0x1403FE3B0;
	invokeGetItem(param1, itemData, param3);
}