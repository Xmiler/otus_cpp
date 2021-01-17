// Адаптер (Adapter)

#include <iostream>

// Example 1.
struct facebookLibrary {

    void login() {
        std::cout << "facebook login" << std::endl;
    }

    void facebook_logout() {
        std::cout << "facebook logout" << std::endl;
    }

    void share() {
        std::cout << "facebook share" << std::endl;
    }

};

struct vkontakeLibrary {

    void connect() {
        std::cout << "vkontake connect" << std::endl;
    }

    void logout() {
        std::cout << "vkontake logout" << std::endl;
    }
    
    void post() {
        std::cout << "vkontake post" << std::endl;
    }

};

struct ILoginAdapter {
    virtual void login() = 0;
    virtual void logout() = 0;
    virtual void post() = 0;
    virtual ~ILoginAdapter() = default;
};

struct FacebookAdapter : public ILoginAdapter {

    void login() override {
        client.login();
    }

    void logout() override {
        client.facebook_logout();
    }

    void post() override {
        client.share();
    }

private:
    facebookLibrary client;
};

struct VkontakteAdapter : public ILoginAdapter {

    void login() override
    {
        client.connect();
    }

    void logout() override
    {
       client.logout();
    }

    void post() override
    {
       client.post();
    }

private:
    vkontakeLibrary client;
};



// Example 2.
struct JSONService {
    bool handle(const std::string& json) {
        // do something very interesting
        std::cout << "Json handling...." << std::endl;
        return true;
    }
};

struct XmlService {
    bool handle(const std::string& xml) {
        const std::string json = xmlToJson(xml);
        return mRealService.handle(json);
    }
private:
    std::string xmlToJson(const std::string& xml) {
        // do convetion here
        std::cout << "Xml convertion" << std::endl;
        return {xml};
    }
    JSONService mRealService;
};

int main(int, char *[]) { 
    std::unique_ptr<ILoginAdapter> curSN = std::make_unique< VkontakteAdapter>();

    curSN->login();
    curSN->post();
    curSN->logout();

    XmlService service;
    service.handle(
        "xml string"
    );

    return 0;
}
