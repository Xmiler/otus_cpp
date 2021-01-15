#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <queue>

class Processor {

    enum class Status {
        normal,
        dynamic
    };

public:
    explicit Processor(int n) : m_n(n), m_status(Status::normal), m_nesting(0) {}
    ~Processor()=default;

    void process(std::stringstream& input) {
        std::string cmd;
        while(std::getline(input, cmd)) {
            process_cmd(cmd);
        }
    }

private:
    const int m_n;
    std::queue<std::string> m_bulk;
    Status m_status;
    int m_nesting;

    void collect(const std::string &cmd) {
        m_bulk.push(cmd);
    }

    void release() {
        while (!m_bulk.empty()) {
            std::cout << m_bulk.front();
            m_bulk.pop();
            if (!m_bulk.empty())
                std::cout << ", ";
            else
                std::cout << std::endl;
        }
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


int main() {

    std::stringstream input("cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n");
    Processor(3).process(input1);

}
