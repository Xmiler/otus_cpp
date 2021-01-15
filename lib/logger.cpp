#include <iostream>
#include "logger.h"

void ConsoleLogger::report(const std::string& message) {
    std::cout << message;
}
