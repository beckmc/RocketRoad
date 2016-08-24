#ifndef SUBMITPOSTUI_H
#define SUBMITPOSTUI_H

#include "../model/usercontainer.h"
#include "../model/postcontainer.h"
#include "../model/user.h"
#include <ncurses.h>
#include <regex>

class SubmitPostUI
{
public:
    SubmitPostUI(UserContainer* user_container, PostContainer* all_posts, User* current_user);
    SubmitPostUI(UserContainer* user_container, PostContainer* all_posts, User* current_user, int group_id);
private:
    void buildScreen();
    void printPrompt();
    UserContainer* user_container_;
    PostContainer* post_container_;
    User* current_user_;
    std::string content_;
    int group_id_;
};

#endif // SUBMITPOSTUI_H
