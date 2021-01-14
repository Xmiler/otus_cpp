#include <iostream>
#include <sstream>
#include <string>
#include <queue>

class Processor {
public:
    explicit Processor(int n) : m_n(n) {}

    void process(const std::string& cmd) {
        m_pool.push(cmd);
        if (m_pool.size() == m_n) {
            release();
        }
    }

private:
    int m_n;
    std::queue<std::string> m_pool;

    void release() {
        while (!m_pool.empty()) {
            std::cout << m_pool.front();
            m_pool.pop();
            if (!m_pool.empty())
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
};


int main() {

    std::stringstream input("cmd1\ncmd2\ncmd3\ncmd4\ncmd5\ncmd6\ncmd7\ncmd8\ncmd9\n");

    auto processor = Processor(3);

    std::string cmd;
    while(std::getline(input, cmd)) {
        processor.process(cmd);
    }

}
