#include <iostream>
#include <sstream>
#include <iterator>
#include <memory>
#include <string>
#include "handler.h"
#include "logger.h"

Handler::Handler(int n) : m_n(n), m_nesting(0) {}

void Handler::process(std::stringstream& input) {
    std::string cmd;
    while(std::getline(input, cmd)) {
        process_cmd(cmd);
    }
}

void Handler::subscribe(ILogger* logger_ptr) {
    m_loggers.insert(logger_ptr);
}

void Handler::unsubscribe(ILogger* logger_ptr) {
    m_loggers.erase(logger_ptr);
}

void Handler::collect(const std::string &cmd) {
    m_bulk.push_back(cmd);
}

void Handler::release() {
    if (m_bulk.empty())
        return;

    std::stringstream output;
    std::copy(m_bulk.begin(), std::prev(m_bulk.end()), std::ostream_iterator<std::string>(output, ", "));
    output << m_bulk.back() << std::endl;
    auto output_str = output.str();

    m_bulk.clear();

    for (const auto& logger : m_loggers )
        logger->report(output_str);
}

void Handler::process_cmd(const std::string& cmd) {
    if (cmd == "{") {
        m_nesting++;
        if (m_nesting == 1)
            release();
    } else if (cmd == "}") {
        m_nesting--;
        if (m_nesting == 0)
            release();
    } else {
        collect(cmd);
        if (m_nesting == 0 && m_bulk.size() == m_n)
            release();
    }
}
