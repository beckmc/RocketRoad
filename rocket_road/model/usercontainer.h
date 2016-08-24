#ifndef USERCONTAINER_H
#define USERCONTAINER_H

#include "user.h"
#include <unordered_map>
#include <string>
#include <stdio.h>
#include <sqlite3.h>
#include <algorithm>

class UserContainer
{
public:
    UserContainer();
    User * findUser(std::string user_id);
    bool addUser(User* user);
    bool get(std::string email);
    bool addFriend(User* user1, User* user2);
    bool removeFriend(User* user1, User* user2);
    bool editFirstName(User* user, std::string new_name);
    bool editLastName(User* user, std::string new_name);
    bool editPassword(User* user, std::string new_pass);
private:
    sqlite3 *db_;
    static std::unordered_map<std::string, User*> all_users_;
    void updateInformation(std::string sql_request);
    static int callbackPopulateUsers(void *data, int argc, char **argv, char **azColName);
    static int callbackUpdateUser(void *data, int argc, char **argv, char **azColName);
};

#endif // USERCONTAINER_H
