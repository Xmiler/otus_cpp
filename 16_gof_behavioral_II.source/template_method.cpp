// Шаблонный метод (Template method)

#include <iostream>

class Report {
    void prepare() {
        std::cout << "===" << std::endl;
        std::cout << "prepare" << std::endl;
    }

    virtual void secure() = 0;

    void aggregate() {
        std::cout << "aggregate" << std::endl;
    }

    virtual void format() = 0;

    void publish() {
        std::cout << "publish" << std::endl;
        std::cout << std::endl;
    }

public:
    void report() {
        prepare();
        secure();
        aggregate();
        format();
        publish();
    }
};

class PublicReport : public Report {
    void secure() override {
        std::cout << "encrypt *" << std::endl;
    }

    void format() override {
        std::cout << "strip *" << std::endl;
    }
};

class InternalReport : public Report {
    void secure() override {
        std::cout << "plane *" << std::endl;
    }

    void format() override {
        std::cout << "human readable *" << std::endl;
    }
};

int main(int, char *[]) {
    PublicReport public_report{};
    public_report.report();

    InternalReport internal_report{};
    internal_report.report();

    return 0;
}
