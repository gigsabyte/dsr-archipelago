#pragma once
#include <string>
#include <iostream>
#include <stdarg.h>

class DSRLogger
{
public:
	void log()
	{
		std::cout << std::endl;
	}
	template<typename T, typename... Types>
	void log(T log, Types... addtlLogs)
	{
		std::cout << log;
		DSRLogger::log(addtlLogs...);
	}

	template<typename T, typename... Types>
	void debug(T log, Types... addtlLogs)
	{
#if _DEBUG
		std::cout << log;
		DSRLogger::debug(addtlLogs...);
#endif
	}
	void debug()
	{
#if _DEBUG
		std::cout << std::endl;
#endif
	}

	template<typename T, typename... Types>
	void error(T errorMsg, Types... addtlErrorMsgs)
	{
		std::cerr << errorMsg;
		DSRLogger::error(addtlErrorMsgs...);
	}
	void error()
	{
		std::cerr << std::endl;
	}
};