#pragma once
#include <iostream>

class ILogger {
public:
    virtual void report(const std::string&) = 0;
};

class ConsoleLogger : public ILogger {
public:
    ConsoleLogger() = default;
    ~ConsoleLogger() = default;

    void report(const std::string& message) override {
        std::cout << message;
    }
};

class FileLogger : public ILogger {
public:
    explicit FileLogger(std::string path) : m_path(std::move(path)) {};

    void report(const std::string& message) override {
        std::cout << "[writing to the file] " << message;
    }

private:
    const std::string m_path;
};