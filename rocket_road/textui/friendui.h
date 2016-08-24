#ifndef FRIENDUI_H
#define FRIENDUI_H

#include <ncurses.h>
#include "../model/usercontainer.h"
#include <algorithm>
#include "menu.h"
#include "userui.h"

class FriendUI
{
public:
    FriendUI(User * logged_user, User * current_user, UserContainer * all_users, Menu * previous_menu);
    void run();
private:
    std::vector<User *> all_friends_;
    User * current_user_;
    UserContainer * all_users_;
    Menu * previous_menu_;
    User * logged_user_;
};

#endif // FRIENDUI_H
