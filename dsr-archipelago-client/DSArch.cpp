#include "DSArch.h"

DSRArch* Arch;

VOID DSRArch::Start() {

	Arch = new DSRArch();

	if (!Arch->Initialize()) {
		__debugbreak();
	};

	while (true) {
		Sleep(1000);
	};

	delete Arch;

	return;
};

BOOL DSRArch::Initialize() {

	FILE* fp;

	AllocConsole();
	SetConsoleTitleA("Dark Souls Remastered Archipelago Console");
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
	printf_s("Starting Dark Souls: Remastered ...\n");

	return true;
}