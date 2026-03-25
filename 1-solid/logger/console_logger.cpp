#include "console_logger.h"

#include <iostream>

void ConsoleLogger::Log(const std::string& s) {
    std::cout << "LOG: " << s.c_str() << std::endl;
}
