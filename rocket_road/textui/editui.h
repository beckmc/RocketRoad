#ifndef EDITUI_H
#define EDITUI_H

#include "../model/usercontainer.h"
#include "../model/user.h"
#include "menu.h"
#include <regex>

class EditUI
{
public:
    EditUI(UserContainer * user_container, User * logged_user);
    void run();
private:
    UserContainer * user_container_;
    User * logged_user_;
};

#endif // EDITUI_H
