// Состояние (State)

#include <iostream>
#include <memory>

// State machine
//                                         
//       error                   success   
//          |                       |      
//          |                       |      
//          / do_it                 / do_it
//          |                       |      
//    +-----|-----+   login   +-----|-----+
//    | Anonymous |-----\-----|   Login   |
//    +-----|-----+           +-----|-----+
//          |                       |      
//          |       logout          |      
//          ----------/-------------|      

namespace problem {

    class Application {
    public:
        void login() {
            if (m_isAnonymous) {
                std::cout << "Login success!" << std::endl;
                m_isAnonymous = false;
            }
            else {
                std::cout << "Already login!" << std::endl;
            }
        }
        void do_it() {
            if (m_isAnonymous) {
                std::cout << "Anonymous error!" << std::endl;
            }
            else {
                std::cout << "Action success!" << std::endl;
            }
        }
        void logout() {
            if (m_isAnonymous) {
                std::cout << "already logout" << std::endl;
            }
            else {
                m_isAnonymous = true;
                std::cout << "logout" << std::endl;
            }
        }
    private:
        bool m_isAnonymous = true;
    };

    void example() {
        std::cout << "problem::example" << std::endl;

        Application app;

        app.do_it();
        app.logout();
        app.login();
        app.do_it();
        app.login();
        app.logout();

        std::cout << std::endl << std::endl;
    }
}

namespace pattern { 

    class Application;

    class ICommandHandler {
    public:
        virtual void login(Application *) = 0;
        virtual void do_it(Application *) = 0;
        virtual void logout(Application *) = 0;
    };

    using ICommandHandlerPtr =  std::unique_ptr<ICommandHandler>;

    class Application {
    public:
        Application();

        void set_current(ICommandHandlerPtr hPtr) {
            m_handler = std::move(hPtr);
        }

        void login() {
            m_handler->login(this);
        }
        void do_it() {
            m_handler->do_it(this);
        }
        void logout() {
            m_handler->login(this);
        }
    private:
        ICommandHandlerPtr m_handler;
    };

    class LoginHandler : public ICommandHandler {
    public:
        void login(Application *) override {
            std::cout << "already login" << std::endl;
        }
        void do_it(Application *) override {
            std::cout << "success" << std::endl;
        }
        void logout(Application *m) override;
    };

    class AnonymousHandler : public ICommandHandler {
    public:
        void login(Application *m) override {
            std::cout << "login success" << std::endl;
            m->set_current(ICommandHandlerPtr{new LoginHandler()});
        }
        void do_it(Application *) override {
            std::cout << "anonymous error" << std::endl;
        }
        void logout(Application *m) override {
            std::cout << "already logout" << std::endl;
            m->set_current(ICommandHandlerPtr{new LoginHandler()});
        }
    };

    void LoginHandler::logout(Application *m) {
        std::cout << "work as anonymous" << std::endl;
        m->set_current(ICommandHandlerPtr{new AnonymousHandler()});
    }

    Application::Application() {
        m_handler = ICommandHandlerPtr{new AnonymousHandler()};
        std::cout << std::endl;
    }

    void example() {
        std::cout << "pattern::example" << std::endl;

        Application app;

        app.do_it();
        app.logout();
        app.login();
        app.do_it();
        app.login();
        app.logout();

        std::cout << std::endl << std::endl;
    }
}


int main(int, char *[]) {

    problem::example();
    
    std::cout << "###############" << std::endl;
    
    
    pattern::example();

    return 0;
}
