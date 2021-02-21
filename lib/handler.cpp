#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include "handler.h"
#include "logger.h"

Handler::Handler(int n) : m_n(n), m_nesting(0), m_timestamp_ptr(nullptr) {}

void Handler::process(std::stringstream& input) {
    std::string cmd;
    while(std::getline(input, cmd)) {
        process_cmd(cmd);
    }
    try_to_release();
}

void Handler::subscribe(ILogger* logger_ptr) {
    m_loggers.insert(logger_ptr);
}

void Handler::unsubscribe(ILogger* logger_ptr) {
    m_loggers.erase(logger_ptr);
}

std::time_t Handler::get_timestamp() {
    if ( m_timestamp_ptr == nullptr )
        throw std::runtime_error("Handler::get_timestamp() was called before the first command was executed.");
    return *m_timestamp_ptr;
}

void Handler::collect(const std::string &cmd) {
    m_bulk.push_back(cmd);
}

void Handler::try_to_release() {
    if (m_bulk.empty())
        return;
    if (m_nesting > 0)
        return;

    if ( m_timestamp_ptr == nullptr )
        m_timestamp_ptr.reset(new std::time_t(std::time(nullptr)));

    std::stringstream output;
    std::copy(m_bulk.begin(), std::prev(m_bulk.end()), std::ostream_iterator<std::string>(output, ", "));
    output << m_bulk.back() << std::endl;
    m_bulk.clear();

    report(output.str());
}

void Handler::report(const std::string& message) {
    for (const auto& logger : m_loggers )
        logger->report(message);
}

void Handler::process_cmd(const std::string& cmd) {
    if (cmd == "{") {
        try_to_release();
        m_nesting++;
    } else if (cmd == "}") {
        m_nesting--;
        try_to_release();
    } else {
        collect(cmd);
        if (m_bulk.size() == m_n)
            try_to_release();
    }
}
