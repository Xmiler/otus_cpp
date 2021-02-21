#include <iostream>
#include <filesystem>

#include "logger.h"
#include "handler.h"

ILogger::ILogger(Handler* handler_ptr) : m_handler_ptr(handler_ptr) {
    m_handler_ptr->subscribe(this);
}

ILogger::~ILogger() {
    m_handler_ptr->unsubscribe(this);
}

StandardLogger::StandardLogger(Handler* handler_ptr, std::ostream& output) : ILogger(handler_ptr), m_output(output) {
}

void StandardLogger::report(const std::string& message) {
    m_output << message;
}

FileLogger::FileLogger(Handler* handler_ptr) : ILogger(handler_ptr), m_ofstream_ptr(nullptr) {
}

void FileLogger::report(const std::string& message) {
    if ( m_ofstream_ptr == nullptr ) {
        std::string log_path = "bulk" + std::to_string(m_handler_ptr->get_timestamp()) + ".log";
        if ( std::filesystem::exists(log_path) )
            throw std::runtime_error("file " + log_path + " already exists.");
        m_ofstream_ptr.reset(new std::ofstream(log_path, std::ofstream::out));
    }
    *m_ofstream_ptr << message;
}
