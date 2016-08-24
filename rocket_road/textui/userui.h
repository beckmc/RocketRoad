#ifndef USERUI_H
#define USERUI_H

#include "../model/user.h"
#include "../model/usercontainer.h"
#include "../model/post.h"
#include "../model/postcontainer.h"
#include "../html/generate.h"
#include "menu.h"
#include "postui.h"
#include "friendui.h"
#include "messageui.h"

class UserUI
{
public:
    UserUI(User* view_user, User* logged_user, UserContainer* user_container, Menu * previous_menu);
    void run();
private:
    User* logged_user_;
    UserContainer* user_container_;
    PostContainer* user_posts_;
    Menu * previous_menu_;
    User* view_user_;
};

#endif // USERUI_H
