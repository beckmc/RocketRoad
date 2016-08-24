#ifndef GROUPUI_H
#define GROUPUI_H

#include "../model/groupcontainer.h"
#include "menu.h"
#include "submitpostui.h"
#include "postui.h"
#include "friendui.h"

class GroupUI
{
public:
    GroupUI(UserContainer * user_container, User * logged_user);
    void run();
private:
    User * logged_user_;
    UserContainer * user_container_;
    std::vector<std::string> all_groupIDs_;
    std::vector<Group *> all_groups_;
    GroupContainer * group_container_;
    void runGroup(Group * group);
};

#endif // GROUPUI_H
