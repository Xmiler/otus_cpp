// Компоновщик (Composite)

#include <iostream>
#include <vector>

namespace bad_case {

    struct File {
        int size();
    };

    struct Directory {
        int size() {
            int result = 0;
            for (auto& file : m_files)
                result += file->size();

            for (auto& directory : m_directories)
                result += directory->size();
            
            return result;
        }

        Directory* parent;
        std::vector<File*> m_files; 
        std::vector<Directory*> m_directories; 
    };

    // And one day .... 
    struct SymLink {
        int size() {
            return 0;
        }

        File* file;
    };

}

struct FileSystemObject {
    virtual int size() = 0;
    virtual void add_object(FileSystemObject *) = 0;
    virtual ~FileSystemObject() = 0;
};

struct File : public FileSystemObject {
    int size() override {
        return 1024;
    }
    
    void add_object(FileSystemObject *) override
    {
        
    }
};

struct SymLink : public FileSystemObject {
    int size() override {
        return 0;
    }
    
    void add_object(FileSystemObject *) override
    {
        
    }
};

struct Directory : public FileSystemObject {
    ~Directory() {
        for (auto p : m_entries)
            // ?
            delete p;
    }

    int size() override {
        int total = 0;
        for(auto fo : m_entries) {
            total += fo->size();
        }
        return total;
    }

    void add_object(FileSystemObject *fso) override {
        m_entries.push_back(fso);
    }
private:
    std::vector<FileSystemObject *> m_entries;
};


Directory* subdir() {
    Directory *d = new Directory;
    d->add_object(new File);
    d->add_object(new File);
    return d;
}

int main(int, char *[]) {
    Directory* root = new Directory();
    root->add_object(subdir());

    std::cout << root->size() << std::endl;

    delete root;

    return 0;
}
