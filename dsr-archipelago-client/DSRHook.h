#pragma once
#include "./submodules/minhook/include/MinHook.h"
#include "DSRLogger.h"

class DSRHook {
public:
	virtual BOOL initialize();
	virtual BOOL enableHook();

private:
	std::shared_ptr<DSRLogger> logger;

};