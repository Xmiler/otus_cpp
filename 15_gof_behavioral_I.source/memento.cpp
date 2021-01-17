// Хранитель (Memento)

#include <iostream>

class Memento {
    friend class Operation;

    int value;
public:
    Memento(int value_) : value(value_) {};
};

class Operation {
    int count = 0;

public:
    void do_it() {
        ++count;
    };

    void dump() {
        std::cout << count << std::endl;
    };

    Memento createSnapshot() {
        return Memento{count};
    }

    void restoreSnapshot(const Memento &memento) {
        count = memento.value;
    }
};



class Operation2 {
    int count = 0;

    struct State {
        friend class Operation2;
        State(int value) : m_value{value} {
        }
    private:
        int m_value;
    };

public:
    void do_it() {
        ++count;
    };

    void dump() {
        std::cout << count << std::endl;
    };

    State state() {
        return State{count};
    }

    void restore(const State &state) {
        count = state.m_value;
    }
};

int main(int, char *[])
{
    std::cout << "Operation1:" << std::endl;

    Operation n;
    n.do_it();

    auto snapshot = n.createSnapshot();

    n.do_it();
    n.dump();

    n.restoreSnapshot(snapshot);
    n.dump();

    std::cout << "Operation2:" << std::endl;

    Operation2 operation2;
    
    auto state = operation2.state();
    
    operation2.do_it();
    operation2.do_it();
    operation2.dump();

    operation2.restore(state);
    operation2.dump();

    return 0;
}
