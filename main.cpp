#include <iostream>
#include <sstream>
#include <string>
#include <queue>

class Processor {

    enum class Status {
        normal,
        dynamic
    };

public:
    explicit Processor(int n) : m_n(n), m_status(Status::normal) {}
    ~Processor()=default;

    void process(const std::string& cmd) {
        switch(m_status) {
            case Status::normal:
                if (cmd == "{") {
                    release();
                    m_status = Status::dynamic;
                }
                else {
                    add(cmd);
                    if ( m_pool.size() == m_n )
                        release();
                }
                break;
            case Status::dynamic:
                if (cmd == "}") {
                    release();
                    m_status = Status::normal;
                }
                else {
                    add(cmd);
                }
                break;
        }

    }

private:
    const int m_n;
    std::queue<std::string> m_pool;
    Status m_status;

    void add(const std::string &cmd) {
        m_pool.push(cmd);
    }

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

    std::stringstream input("cmd1\ncmd2\n{\ncmd3\ncmd4\ncmd5\ncmd6\n}\ncmd7\ncmd8\ncmd9\ncmd10\ncmd11\ncmd12\n");

    auto processor = Processor(3);

    std::string cmd;
    while(std::getline(input, cmd)) {
        processor.process(cmd);
    }

}
