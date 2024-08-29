#include "DSArch.h"

DSRArch* Arch;
DSRHook* Hook;
DSRLogger* Logger;

VOID DSRArch::start() {

	Logger = new DSRLogger();
	Arch = new DSRArch();

	if (!Arch->initialize()) {
		Sleep(10000);
		__debugbreak();
	};

	Sleep(2000);
	Hook->enableHook();

	while (true) {
		Sleep(1000);
	};

	delete Arch;
	delete Hook;
	delete Logger;

	return;
};

BOOL DSRArch::initialize() {

	FILE* fp;

	AllocConsole();
	SetConsoleTitleA("Dark Souls Remastered Archipelago Console");
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);


	Logger->log("Starting Dark Souls: Remastered ...");

	Hook = new DSRHook();

	BOOL initialized = false;
	
	try {
		Logger->log("Initializing!");
		initialized = Hook->initialize();
		Logger->log("Initialized!");
	}
	catch (const std::exception&) {
		Logger->error("Encountered exception");
	}

	// Start command prompt
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Arch->readInput, NULL, NULL, NULL);

	return initialized;
}

VOID DSRArch::readInput() {
	while (true) {
		std::string line;
		std::getline(std::cin, line);

#if _DEBUG
		if (line == "p") {
			Logger->log("Giving prism stone...");
			Hook->giveItem(0, 5);
		}
		else if (line == "l") {
			Logger->log("Giving Lordvessel...");
			Hook->giveItem(0x400009CE, 1);
		}
		else if (line == "z") {
			Logger->log("Giving Zweihander...");
			Hook->giveItem(0x00055730, 1);
		}
#endif
	}
}