#include "DSArch.h"

DSRArch* Arch;
DSRHook* Hook;

VOID DSRArch::start() {

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

	return;
};

BOOL DSRArch::initialize() {

	FILE* fp;

	logger = DSRLogger::get();

	AllocConsole();
	SetConsoleTitleA("Dark Souls Remastered Archipelago Console");
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);


	logger->log("Starting Dark Souls: Remastered ...\n");

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

	// Start command prompt
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Arch->readInput, NULL, NULL, NULL);

	return initialized;
}

VOID DSRArch::readInput() {
	while (true) {
		std::string line;
		std::getline(std::cin, line);

		if (line == "p") {
			std::cout << "Giving item..." << std::endl;
			Hook->giveItem(0, 5);
		}
	}
}