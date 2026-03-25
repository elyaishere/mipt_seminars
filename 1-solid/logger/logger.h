#pragma once
#include <string>

struct ILogger {
    virtual ~ILogger() = default;
    virtual void Log(const std::string& s) = 0;
};
