#ifndef SEARCH_H
#define SEARCH_H

#include "user.h"
#include "usercontainer.h"
#include <vector>
#include "sqlite3.h"

class Search
{
public:
    Search(UserContainer* user_container);
    std::vector<User *> findUser(std::string searchPhrase);
private:
    sqlite3 *db_;
    static UserContainer* user_container_;
    static std::vector<User*> return_users_;
    static int callbackFindUsers(void *data, int argc, char **argv, char **azColName);
};

#endif // SEARCH_H
