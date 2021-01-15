#include <iostream>

#include "logger.h"
#include "handler.h"

ILogger::ILogger(Handler* handler_ptr) : m_handler_ptr(handler_ptr) {
    m_handler_ptr->subscribe(this);
}

ILogger::~ILogger() {
    m_handler_ptr->subscribe(this);
}

ConsoleLogger::ConsoleLogger(Handler* handler_ptr) : ILogger(handler_ptr) {
}

void ConsoleLogger::report(const std::string& message) {
    std::cout << message;
}

FileLogger::FileLogger(Handler* handler_ptr, std::string path) : ILogger(handler_ptr), m_outfile(std::move(path), std::ofstream::out) {

}

void FileLogger::report(const std::string& message) {
    m_outfile << message;
}
