#pragma once
#include <iostream>
#include <sstream>
#include <iterator>
#include <memory>
#include <string>
#include <list>
#include "logger.h"

class Handler {
public:
    explicit Handler(int n) : m_n(n), m_nesting(0) {}
    ~Handler()=default;

    void process(std::stringstream& input) {
        std::string cmd;
        while(std::getline(input, cmd)) {
            process_cmd(cmd);
        }
    }

    void subscribe(std::shared_ptr<ILogger> logger_ptr) {
        m_loggers.push_back(logger_ptr);
    }

private:
    const int m_n;
    std::list<std::string> m_bulk;
    int m_nesting;
    std::list<std::shared_ptr<ILogger>> m_loggers;

    void collect(const std::string &cmd) {
        m_bulk.push_back(cmd);
    }

    void release() {
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

    void process_cmd(const std::string& cmd) {
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
};
