#pragma once
#include <list>
#include <unordered_set>
#include "handler.h"

class ILogger;

class Handler {
public:
    explicit Handler(int);
    ~Handler()=default;

    void process(std::stringstream&);

    void subscribe(ILogger*);
    void unsubscribe(ILogger*);

private:
    const int m_n;
    std::list<std::string> m_bulk;
    int m_nesting;
    std::unordered_set<ILogger*> m_loggers;

    void collect(const std::string&) ;
    void release();
    void process_cmd(const std::string&);
    void report(const std::string&);
};
