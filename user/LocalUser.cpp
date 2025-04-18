#include "User.hpp"
#include "Screen.hpp"

class LocalUser : public User
{
private:
    std::string username;

public:
    void getUserInfo(std::unique_ptr<Screen> &screen) override
    {
        username = screen->readInput("Enter Username");
    }

    std::string &getName() override
    {
        return username;
    }
};

__attribute__((constructor)) void initLocalUser()
{
    UserFactory::registerUserCreator("local", []() -> std::unique_ptr<User>
                                     { return std::make_unique<LocalUser>(); });
}