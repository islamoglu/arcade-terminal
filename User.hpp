#pragma once

#include <string>

class User
{
private:
    std::string name;

public:
    User(std::string &name) { this->name = name; }
    void setName(std::string &name) { this->name = name; }
    std::string &getName() { return name; }
};

class UserManager
{
public:
    static User *getUser();
};