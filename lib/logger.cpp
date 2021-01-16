#include <iostream>

#include "logger.h"
#include "handler.h"

ILogger::ILogger(Handler* handler_ptr) : m_handler_ptr(handler_ptr) {
    m_handler_ptr->subscribe(this);
}

ILogger::~ILogger() {
    m_handler_ptr->subscribe(this);
}

StandardLogger::StandardLogger(Handler* handler_ptr, std::ostream& output) : ILogger(handler_ptr), m_output(output) {
}

void StandardLogger::report(const std::string& message) {
    m_output << message;
}

FileLogger::FileLogger(Handler* handler_ptr, std::string path) : ILogger(handler_ptr), m_outfile(std::move(path), std::ofstream::out) {

}

void FileLogger::report(const std::string& message) {
    m_outfile << message;
}
