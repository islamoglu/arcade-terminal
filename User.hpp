#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include "Config.hpp"
#include "Screen.hpp"

class User
{
public:
    virtual std::string &getName() = 0;
    virtual void getUserInfo(std::unique_ptr<Screen> &screen) = 0;
};

class UserFactory
{
private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<User>()>> *userCreators;

public:
    static void registerUserCreator(std::string type, std::function<std::unique_ptr<User>()> creator);
    static std::unique_ptr<User> createUser(std::unique_ptr<Config> &config);
};