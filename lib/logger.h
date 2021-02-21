#pragma once
#include <iostream>
#include <fstream>
#include <memory>
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

class StandardLogger : public ILogger {
public:
    explicit StandardLogger(Handler*, std::ostream& input = std::cout);
    ~StandardLogger() override = default;

    void report(const std::string& message) override;

private:
    std::ostream& m_output;
};

class FileLogger : public ILogger {
public:
    FileLogger(Handler*);

    void report(const std::string& message) override;

private:
    std::unique_ptr<std::ofstream> m_ofstream_ptr;
};