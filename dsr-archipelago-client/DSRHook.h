#pragma once
#include "./submodules/minhook/include/MinHook.h"
#include "DSRLogger.h"

class DSRHook {
public:
	virtual BOOL initialize();
	virtual BOOL enableHook();
	virtual VOID giveItem(uint32_t itemId, int amount);
private:
	std::shared_ptr<DSRLogger> logger;

};