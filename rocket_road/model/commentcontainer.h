#ifndef COMMENTCONTAINER_H
#define COMMENTCONTAINER_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "comment.h"
#include "post.h"
#include "log.h"
#include "usercontainer.h"

#include <ncurses.h>

class CommentContainer
{
public:
    CommentContainer(Post *post, UserContainer *user_container);
    CommentContainer(Post *post, UserContainer *user_container, int isGroupComment);
    std::vector<Comment*> getComments();
    bool send_comment(std::string content, User* user, std::string postID);
    bool send_comment_group(std::string content, User *user, std::string postID);
private:
    Log log;
    sqlite3 *db_;
    static Post* post_;
    static UserContainer* user_container_;
    static std::vector<Comment*> comment_vector_;
    static int callbackPopulateComments(void *data, int argc, char **argv, char **azColName);
    static int callbackWriteComment(void *data, int argc, char **argv, char **azColName);
};

#endif // COMMENTCONTAINER_H
