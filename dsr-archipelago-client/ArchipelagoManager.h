#pragma once

#include "DSRHook.h"
#include "DSRLogger.h"
#include "submodules/apclientpp/apclient.hpp"
#include "submodules/apclientpp/apuuid.hpp"

class ArchipelagoManager
{
	BOOL initialize(std::string uri);
	VOID say(std::string message);
	BOOL isConnected();
	VOID update();
	VOID gameFinished();
};

