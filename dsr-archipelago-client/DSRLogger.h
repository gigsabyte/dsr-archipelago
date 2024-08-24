#pragma once
#include <string>
#include <iostream>
class DSRLogger
{
public:
    DSRLogger(DSRLogger const&) = delete;
    DSRLogger& operator=(DSRLogger const&) = delete;

    static std::shared_ptr<DSRLogger> get()
    {
        static std::shared_ptr<DSRLogger> s{ new DSRLogger };
        return s;
    }

	void log(std::string logMessage) {

        std::cout << logMessage << std::endl;
	}

private:
    DSRLogger() {}
};

