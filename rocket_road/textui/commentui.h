#ifndef COMMENTUI_H
#define COMMENTUI_H

#include <vector>
#include <string>
#include <ncurses.h>
#include <regex>
#include "../model/post.h"
#include "../model/comment.h"
#include "../model/user.h"
#include "../model/commentcontainer.h"

class CommentUI
{
public:
    CommentUI(Post* post, User* current_user, UserContainer *user_container);
    CommentUI(Post* post, User* current_user, UserContainer *user_container, bool is_group);
    void buildScreen();
    void printPost();
    void printComments();
    void printPrompt();
private:
    Post* post_;
    User* current_user_;
    CommentContainer* comment_container_;
    bool is_group_;
};

#endif // COMMENTUI_H
