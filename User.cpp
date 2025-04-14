#include "User.hpp"
#include "Screen.hpp"
#include "Config.hpp"
#include "Log.hpp"
#include <stdexcept>
#include <memory>

class UserReader
{
public:
    virtual User *readUser() = 0;
};

class TerminalUserReader : public UserReader
{
public:
    User *readUser() override
    {
        Screen &screen = ScreenManager::getScreen();
        std::string username = screen.readInput("Username");
        screen.clean();
        return new User(username);
    }
};

User *UserManager::getUser()
{
    std::unique_ptr<UserReader> reader;

    const std::string &userType = ConfigManager::getConfig().getValue("userType");
    if (userType == "terminal")
    {
        reader = std::make_unique<TerminalUserReader>();
    }
    else
    {
        throw std::runtime_error("Unknown user type: " + userType);
    }

    return reader->readUser();
}
