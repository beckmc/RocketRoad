#ifndef POSTUI_H
#define POSTUI_H

#include "../model/postcontainer.h"
#include "../model/usercontainer.h"
#include "../model/date.h"
#include "commentui.h"
#include <algorithm>
#include <ncurses.h>

class PostUI
{
public:
    PostUI(PostContainer * all_posts, User *current_user, UserContainer *user_container);
    PostUI(PostContainer * all_posts, User *current_user, UserContainer *user_container, bool is_group);
    int selectOption();
    void buildScreen();
    void printPost();
    void buildMenu();
    void moveCursor(int index);
    void postCheck();
private:
    UserContainer* user_container_;
    std::vector<Post*> all_posts_;
    User * current_user_;
    PostContainer* post_container_;
    int post_index_;
    int choice_index_;
    bool has_next_;
    bool has_previous_;
    bool done_ = false;
    bool is_group_;
};

#endif // POSTUI_H
