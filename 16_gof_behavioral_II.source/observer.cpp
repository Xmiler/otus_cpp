// Наблюдатель (Observer)

#include <iostream>
#include <vector>

enum class Lang {
    ru, en
};

// Observer or Sibscriber
class Observer {
public:
    virtual void update(Lang lang) = 0;
};

// Observable or Publisher
class Observable {
public:
    virtual void subscribe(Observer* obs) = 0;
};

class Language : public Observable {
public:
    void subscribe(Observer *obs) override {
        subs.push_back(obs);
    }

    void set_language(Lang lang_) {
        lang = lang_;
        notify();
    }

    void notify() {
        for (auto s : subs) {
            s->update(lang);
        }
    }
private:
    Lang lang{Lang::ru};
    std::vector<Observer *> subs;
};

class Report : public Observer {
public:
    Report(Language *lang) {
        lang->subscribe(this);
    }

    void update(Lang lang) override {
        std::cout << "switch report template to lang " << int(lang) << std::endl;
    }
};

class UserInterface : public Observer {
public:
    UserInterface(Language *lang) {
        lang->subscribe(this);
    }

    void update(Lang lang) override {
        std::cout << "refresh ui for lang " << int(lang) << std::endl;
    }
};

int main(int, char *[]) {
    Language lang;

    Report rpt(&lang);
    UserInterface ui(&lang);

    lang.set_language(Lang::ru);

    lang.set_language(Lang::en);

    return 0;
}
