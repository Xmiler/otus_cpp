// Команда (Command)

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>


class Document {
public:
    void create() {
        std::cout << "new document" << std::endl;
    }

    void paragraph(const std::string &text) {
        m_text += text + "\n";
        std::cout << "new paragraph " << text << std::endl;
    }

    void saveAs(const std::string &name) {
        std::cout << "--- " << name << "---" << std::endl;
        std::cout << m_text << std::endl;
    }
private:
    std::string m_text;
};

class ICommand {
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
};


class Command : public ICommand {
public:
    virtual ~Command() = default;
protected:
    Command(Document *d)
        : document(d) {

    }
    Document * document;
};


class NewDocumentCommand : public Command {
public:
    NewDocumentCommand(Document * d) 
        : Command(d) {

    }

    void execute() override {
        document->create();
    }
};


class ParagraphCommand : public Command { 
public:
    ParagraphCommand(Document * d, const std::string &text_) 
        : Command(d)
        , m_text(text_) {

    }

    void execute() override {
        document->paragraph(m_text);
    }
private:
    std::string m_text;
};


class SaveAsCommand : public Command {
public:
    SaveAsCommand(Document * d, const std::string &fname_) 
        : Command(d)
        , m_fname(fname_) {

    }

    void execute() override {
        document->saveAs(m_fname);
    }
private:
    std::string m_fname;
};


class MacroCommand : public ICommand {
public:
    MacroCommand() = default; 
    ~MacroCommand() = default; 

    void addCommand(std::unique_ptr<ICommand> cmd) {
        m_commands.emplace_back(std::move(cmd));
    }

    void execute() override {
        for (auto& cmd : m_commands)
            cmd->execute();
    }
private:
    std::vector<std::unique_ptr<ICommand>> m_commands;
};


namespace one_more_example {
    class Controller {
    public:
        void scheduleCommand(std::unique_ptr<Command> cmdPtr) {
            // lock
            m_commands.emplace_back(std::move(cmdPtr));
            // add to history
            // unlock
        }
    private:
        void workerThread() {
            // wait for command
            for (auto& cmd : m_commands)
                cmd->execute();
            // execute command
        }

        std::list<std::unique_ptr<Command>> m_commands;
    };
}

namespace empty_example {
    class EmptyCommand : public ICommand {
        void execute() override {
        }
    };

    class Button {
    public:
        Button(const std::string& name) 
            : m_name{name},
            m_command{std::make_unique<EmptyCommand>()} {

        }

        Button(const std::string& name, std::unique_ptr<ICommand> cmdPtr)
            : m_name{name}
            , m_command{std::move(cmdPtr)} {

        }

        void draw() {

        }

        void press() {
            m_command->execute();
        }

    private:
        std::string m_name;
        std::unique_ptr<ICommand> m_command;
    };
}

int main() {
    Document doc;

    //history, snapshot, backup
    std::vector<Command *> history;
    history.push_back(new NewDocumentCommand(&doc));
    history.push_back( new ParagraphCommand(&doc, "Manual"));
    history.push_back( new ParagraphCommand(&doc, ""));
    history.push_back( new ParagraphCommand(&doc, "Hello, World!"));
    history.push_back( new SaveAsCommand(&doc, "hello.doc"));

    for(auto c: history) {
        c->execute();
    }

    std::cout << "\nMacroCommand example:" << std::endl;

    MacroCommand macroCommand;
    macroCommand.addCommand(
        std::unique_ptr<ICommand>(new NewDocumentCommand(&doc))
    );
    macroCommand.addCommand(
        std::unique_ptr<ICommand>(new ParagraphCommand(&doc, "Manual"))
    );
    macroCommand.addCommand(
        std::unique_ptr<ICommand>(new ParagraphCommand(&doc, ""))
    );
    macroCommand.addCommand(
        std::unique_ptr<ICommand>(new ParagraphCommand(&doc, "Hello, World!"))
    );
    macroCommand.execute();

    std::cout << "\nEmptyCommand example:" << std::endl;
    empty_example::Button emptyButton{"empty"};
    emptyButton.press();

    return 0;
}
