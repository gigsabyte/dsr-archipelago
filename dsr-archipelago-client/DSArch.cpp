#include "DSArch.h"

DSRArch* Arch;
DSRHook* Hook;

VOID DSRArch::Start() {

	Arch = new DSRArch();

	if (!Arch->Initialize()) {
		Sleep(100000);
		__debugbreak();
	};

	for (int i = 0; i < 5; ++i) {
		Sleep(1000);
	}
	Hook->enableHook();

	while (true) {
		Sleep(1000);
	};

	delete Arch;

	return;
};

BOOL DSRArch::Initialize() {

	FILE* fp;

	logger = DSRLogger::get();

	AllocConsole();
	SetConsoleTitleA("Dark Souls Remastered Archipelago Console");
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);


	logger->log ("Starting Dark Souls: Remastered ...\n");

	Hook = new DSRHook();

	BOOL initialized = false;
	
	try {
		logger->log("initializing!");
		initialized = Hook->initialize();
		logger->log("initialized!");
	}
	catch (const std::exception&) {
		logger->log("Encountered exception");
	}
	

	return initialized;
}