#ifndef LOGINUI_H
#define LOGINUI_H

#include <ncurses.h>
#include <string>
#include "../model/user.h"
#include "../model/login.h"
#include "../model/usercontainer.h"
#include "../model/signup.h"
#include "menu.h"


class LoginUI
{
public:
    LoginUI(UserContainer * user_container);
    User* run();
private:
    Login login_;
    User* start();
    User* signup();
    User* tryUsername();
    User* tryPassword(User * current_user);
    UserContainer* user_container_;
};

#endif // LOGINUI_H
