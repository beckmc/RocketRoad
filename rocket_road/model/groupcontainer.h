#ifndef GROUPCONTAINER_H
#define GROUPCONTAINER_H

#include "group.h"
#include "user.h"
#include <unordered_map>
#include <string>
#include <stdio.h>
#include <sqlite3.h>

class GroupContainer
{
public:
    GroupContainer();
    Group * findGroup(int group_id);
    bool addGroup(Group* group);
    bool addUser(User* user, int group_id);
    bool removeUser(User* user, int group_id);
private:
    sqlite3 *db_;
    static std::unordered_map<int, Group*> all_groups_;
    static int callbackPopulateGroups(void *data, int argc, char **argv, char **azColName);
    static int callbackUpdateGroups(void *data, int argc, char **argv, char **azColName);
};
#endif // GROUPCONTAINER_H
