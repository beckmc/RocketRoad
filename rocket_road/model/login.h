#ifndef LOGIN_H
#define LOGIN_H
#include "user.h"
#include "usercontainer.h"
#include <string>
#include <iostream>

class Login
{
public:
    Login();
    Login(UserContainer * user_container);
    void operator=(Login &other);
    bool testUsername(std::string input);
    bool testPassword(User * user, std::string input);
    UserContainer * getContainer();
    User * loadUser(std::string input);
private:
    UserContainer * user_container_;
};

#endif // LOGIN_H
