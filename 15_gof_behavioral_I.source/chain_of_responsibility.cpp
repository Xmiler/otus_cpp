// Цепочка ответственности (Chain of responsibilily)

#include <iostream>
#include <string>
#include <vector>

namespace basic {

    struct Email {
        // headers
        // body
        // etc... 
    };

    class SpamFilter_Level1 {
    public:
        bool filter(const Email&) {
            // Many-many lines of code here
            return false;
        }
    };

    class SpamFilter_Level2 {
    public:
        bool filter(const Email& ) {
            // Many-many lines of code here
            return false;
        }
    };

    class SpamFilter {
    public:
        bool filter(const Email& email) {
            if (level1.filter(email))
                return true;
            if (level2.filter(email))
                return true;
            // ...
            // many-many other if
        }
    private:
        SpamFilter_Level1 level1;
        SpamFilter_Level2 level2;
        // ... many other levels here
    };

    class ISpamFilter {
    public:
        virtual bool filter(const Email&) = 0;
    };

    class SpamFilter2 {
    public:
        bool filter(const Email& mail) {
            bool result = false;
            for (auto& filter : m_filters) {
                if (filter->filter(mail)) {
                    result = true;
                    break;
                }
            }
            return result;
        }
    private:
        std::vector<ISpamFilter*> m_filters;
    };

}

namespace pattern {

    class Handler {
    public:
        Handler() 
            : m_next(nullptr) {

        }

        void add(Handler *n) {
            if (m_next)
                m_next->add(n);
            else
                m_next = n;
        }

        virtual void exec(const std::string &line) {
            if (m_next) {
                m_next->exec(line);
            }
        }
    private:
        Handler* m_next;
    };


    class DropHandler : public Handler {
    public:
        void exec(const std::string &line) override {
            
            if (line.find("DROP") == 0) {
                std::cout << "DropHandler accept " << line << std::endl;
            } else {
                std::cout << "DropHandler pass" << std::endl;
                Handler::exec(line);
            }
        }
    };

    class SelectHandler : public Handler {
    public:
        void exec(const std::string &line) override {
            if (line.find("SELECT") == 0) {
                std::cout << "SelectHandler accept " << line << std::endl;
            } else {
                std::cout << "SelectHandler pass" << std::endl;
                Handler::exec(line);
            }
        }
    };

    class CreateHandler: public Handler {
    public:
        void exec(const std::string &line) override {
            if (line.find("CREATE") == 0) {
                std::cout << "CreateHandler accept " << line << std::endl;
            } else {
                std::cout << "CreateHandler pass" << std::endl;
                Handler::exec(line);
            }
        }
    };

    void example() {
        DropHandler handler;

        SelectHandler select;
        CreateHandler create;

        handler.add(&select);
        handler.add(&create);

        handler.exec("CREATE table");
        handler.exec("SELECT * FROM table");
        handler.exec("DROP table");
    }

}

int main(int, char *[])
{
    pattern::example();

    return 0;
}
