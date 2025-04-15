#include "User.hpp"
#include "Screen.hpp"
#include "Config.hpp"
#include <stdexcept>
#include <memory>

std::unordered_map<std::string, std::function<std::unique_ptr<User>()>> *UserFactory::userCreators = nullptr;

void UserFactory::registerUserCreator(std::string type, std::function<std::unique_ptr<User>()> creator)
{
    if (userCreators == nullptr)
    {
        userCreators = new std::unordered_map<std::string, std::function<std::unique_ptr<User>()>>();
    }
    userCreators->insert({type, creator});
}

std::unique_ptr<User> UserFactory::createUser(std::unique_ptr<Config> &config)
{
    std::string userType = config->getValue("userType");
    std::function<std::unique_ptr<User>()> creator = userCreators->at(userType);
    return creator();
}
