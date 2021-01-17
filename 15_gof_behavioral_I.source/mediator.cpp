// Посредник (Mediator)

#include <iostream>
#include <map>
#include <set>
#include <string>

namespace example1 {
    enum class Role {
        user, admin
    };

    struct User {
        std::string name;
        Role role;
    };

    class Permissions {
        std::map<std::string, Role> ops = {
            {"drop", Role::admin},  
            {"create", Role::admin},
            {"select", Role::user}
        };

    public:
        bool isPermit(const std::string &op, Role role) {
            auto i = ops.find(op);
            if (i != std::end(ops)) {
                return i->second == role;
            }
            return false;
        }
    };
}

namespace example2 {

namespace wrong {

    class Edit {
    public:
        void changeText() {

        }
    };

    class Speaker {
    public:
        void speak() {

        }
    };

    class Button {
    public:
        void push() {
            edit.changeText();
            speaker.speak();
        }
        
    private:
        Edit& edit;
        Speaker& speaker;
    };

}

namespace pattern {
    struct Event {
        enum class Type {
            ButtonPress = 0
        };
        Type type;
        std::string data;
    };

    class IController {
    public:
        virtual void handleEvent(const Event& ) = 0;
    };

    class Button {
    public:
        void push() {
            Event event;
            event.type = Event::Type::ButtonPress;
            event.data = "Button name";
            controller->handleEvent(event);
        }
    private:
        IController* controller;
    };

    class Edit {
    public:
        void changeText() {

        }
    };

    class Speaker {
    public:
        void speak() {

        }
    };

    class Controller : public IController {
    public:
        void handleEvent(const Event& event) override {
            if (event.type == Event::Type::ButtonPress) {
                edit.changeText();
                speaker.speak();
            }
        }
    private:
        Button button;
        Edit edit;
        Speaker speaker;
    };

}

}

int main(int, char *[])
{
    {
        using namespace example1;
        Permissions perm;

        auto v = User{"Vasia", Role::user};
        auto p = User{"Petia", Role::admin};

        std::cout << perm.isPermit("drop", v.role) << std::endl;
        std::cout << perm.isPermit("drop", p.role) << std::endl;
    }

    return 0;
}
