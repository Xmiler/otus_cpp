// Декоратор (Decorator)

#include <iostream>
#include <memory>

struct File {
    virtual void write() = 0;
    virtual void SetHeader(int val) = 0;
    virtual ~File() = default;
};


struct RawFile : public File {

    void write() override {
        std::cout << "write" << std::endl;
    }
    
    virtual void SetHeader(int val)
    {
        std::cout << "write" << std::endl;
    }
};

struct ZipFile : public File {

    ZipFile(File *file_) : file(file_) {};

    ~ZipFile() {
        delete file;
    }
    
    virtual void SetHeader(int val)
    {
        file->SetHeader(val);
    }

    void write() override {
        std::cout << "decompress" << std::endl;
        file->write();
        std::cout << "compress" << std::endl;
    }
private:
    File *file;

};

struct CryptFile : public File {

    CryptFile(File *file_) : file(file_) {};
    
    ~CryptFile() {
        delete file;
    }
    
    virtual void SetHeader(int val)
    {
        file->SetHeader(val);
    }
    
    void write() override {
        std::cout << "decrypt" << std::endl;
        file->write();
        std::cout << "crypt" << std::endl;
    }

private:
    File *file;

};

int main(int, char *[]) {
    std::unique_ptr<File> rawFile = std::make_unique<RawFile>();
    rawFile->write();

    std::unique_ptr<File> zipFile = std::make_unique<ZipFile>(new RawFile{});
    zipFile->write();

    return 0;
}
