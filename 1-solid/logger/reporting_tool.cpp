#include "reporting_tool.h"
#include "logger.h"

ReportingTool::ReportingTool(std::shared_ptr<ILogger> logger) : logger(std::move(logger)) {
}

void ReportingTool::Report(const std::string& s) {
    logger->Log(s);
}
