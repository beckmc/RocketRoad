#ifndef GENERATE_H
#define GENERATE_H

#include "../model/user.h"
#include "../model/usercontainer.h"
#include "../model/post.h"
#include "../model/postcontainer.h"
#include "../model/comment.h"
#include "../model/commentcontainer.h"
#include <iostream>
#include <fstream>
#include <algorithm>

class Generate
{
public:
    Generate(User* user, User * logged_user, UserContainer* user_container);
    void run();
private:
    User* logged_user_;
    User* user_;
    UserContainer* user_container_;
    std::vector<Post*> posts_;
    bool generate();
    void open();
};

#endif // GENERATE_H
