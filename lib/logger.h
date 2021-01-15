#pragma once
#include <iostream>
#include <fstream>
#include <unordered_set>

class Handler;

class ILogger {
public:
    explicit ILogger(Handler* handler_ptr);
    virtual ~ILogger();

    virtual void report(const std::string&) = 0;

protected:
    Handler* m_handler_ptr;
};

class ConsoleLogger : public ILogger {
public:
    explicit ConsoleLogger(Handler*);
    ~ConsoleLogger() override = default;

    void report(const std::string& message) override;

};

class FileLogger : public ILogger {
public:
    explicit FileLogger(Handler*, std::string);

    void report(const std::string& message) override;

private:
    std::ofstream m_outfile;
};