#pragma once

#include "logger.h"

struct ConsoleLogger : ILogger {
    void Log(const std::string& s) override;
};
