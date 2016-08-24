#ifndef SEARCHUI_H
#define SEARCHUI_H

#include <ncurses.h>
#include "../model/search.h"
#include <vector>
#include "../model/user.h"
#include "../model/usercontainer.h"
#include <regex>
#include "menu.h"
#include "userui.h"

class SearchUI
{
public:
    SearchUI(UserContainer * user_container, User * logged_user);
    void run();
private:
    UserContainer * user_container_;
    std::vector<std::string> search(std::string search_phrase);
    std::vector<User *> found_users_;
    User * logged_user_;
};

#endif // SEARCHUI_H
