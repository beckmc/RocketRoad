#ifndef LOGINUI_H
#define LOGINUI_H

#include <ncurses.h>
#include "../model/user.h"
#include "../model/login.h"
#include "../model/usercontainer.h"

class LoginUI
{
public:
    LoginUI(UserContainer* user_container);
    void run();
    void tryUsername();
    void tryPassword(User* current_user);
};

#endif // LOGINUI_H
