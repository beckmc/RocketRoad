#ifndef POSTCONTAINER_H
#define POSTCONTAINER_H

#include "post.h"
#include "usercontainer.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

class PostContainer
{
public:
    PostContainer(std::vector<std::string> posterIDs, UserContainer *user_container);
    PostContainer(std::string group_id);
    std::vector<Post*> get_posts();
    bool send_post(std::string content, User* user);
    bool send_post(std::string content, User* user, std::string group_id);
    bool like_post(Post* post, User *user);
    bool unlike_post(Post* post, User *user);
    bool refreshPost(Post* post);
    bool like_post_group(Post* post, User *user);
    bool unlike_post_group(Post* post, User *user);
    bool refreshPost_group(Post* post);
private:
    sqlite3 *db_;
    static UserContainer * user_container_;
    static std::vector<Post*> posts_;
    static int callbackPopulatePosts(void *data, int argc, char **argv, char **azColName);
    static int callbackWritePost(void *NotUsed, int argc, char **argv, char **azColName);
    static int callbackRefreshPost(void *NotUsed, int argc, char **argv, char **azColName);
    static int callbackPopulateGroupPosts(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif // POSTCONTAINER_H
