#pragma once
#include <list>
#include <unordered_set>
#include <memory>
#include <ctime>

class ILogger;

class Handler {
public:
    explicit Handler(int);
    ~Handler()=default;

    void process(std::stringstream&);

    void subscribe(ILogger*);
    void unsubscribe(ILogger*);

    std::time_t get_timestamp();

private:
    const int m_n;
    std::list<std::string> m_bulk;
    int m_nesting;
    std::unordered_set<ILogger*> m_loggers;
    std::unique_ptr<std::time_t> m_timestamp_ptr;

    void collect(const std::string&) ;
    void try_to_release();
    void process_cmd(const std::string&);
    void report(const std::string&);
};
