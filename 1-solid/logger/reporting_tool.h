#pragma once
#include <memory>
#include <string>

struct ILogger;

class ReportingTool {
    std::shared_ptr<ILogger> logger;

public:
    ReportingTool(std::shared_ptr<ILogger> logger);

    void Report(const std::string& s);
};
