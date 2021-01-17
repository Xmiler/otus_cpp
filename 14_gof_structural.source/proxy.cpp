// Заместитель (Proxy)

#include <iostream>
#include <vector>

struct ILogger {
    virtual void info() = 0;

    virtual void error() = 0;

    virtual ~ILogger() = default;
};

struct Logger : public ILogger {

    void info() override {
        std::cout << "info" << std::endl;
    }

    void error() override {
        std::cout << "error" << std::endl;
    }
};

struct LevelLogger : public ILogger {
    LevelLogger(int level_, ILogger *logger_) : level(level_), logger(logger_) {};

    ~LevelLogger() {
        delete logger;
    }

    void info() override {
        ///do something
        if (level > 0) {
            logger->info();
        }
    }

    void error() override {
        logger->error();
    }

private:
    int level;
    ILogger *logger;
};

int main(int, char *[]) {
    std::unique_ptr<ILogger> logger = std::make_unique<LevelLogger>(0, new Logger{});

    logger->info();
    logger->error();

    std::vector<bool> vec{true, false, true, false};
    auto value = vec.at(2);

    return 0;
}
