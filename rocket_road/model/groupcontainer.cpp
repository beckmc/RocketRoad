#include "groupcontainer.h"

std::unordered_map<int, Group*> GroupContainer::all_groups_;

/**
 * @brief GroupContainer::GroupContainer Basic Constructor. Retrieves all data from the database.
 */
GroupContainer::GroupContainer()
{
    all_groups_.clear();
    int code;
    char *sql;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in GroupContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    sql = "SELECT * FROM groups";

    code = sqlite3_exec(db_, sql, callbackPopulateGroups, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}

/**
 * @brief GroupContainer::callbackPopulateGroups Callback function for group generation.
 * Retrieves all groups and generates their objects.
 */
int GroupContainer::callbackPopulateGroups(void *data, int argc, char **argv, char **azColName){
    int i;
    int id = 0;
    std::string idString;
    std::string name = "";
    std::string description = "";
    std::string members = "";
    std::string startDate = "";
    std::string endDate = "";
    for(i=0; i<argc; i++){
        switch(i)
        {
        case 0:
            idString = argv[i];
            id = std::stoi(idString);
            break;
        case 1:
            name = argv[i];
            break;
        case 2:
            description = argv[i];
            break;
        case 3:
            members = argv[i] ? argv[i] : "";
            break;
        case 4:
            startDate = argv[i];
            break;
        case 5:
            endDate = argv[i];
            break;
        }
    }
    Group* group = new Group(id, name, description, members, startDate, endDate);
    std::pair<int, Group*> current_group (group->getID(), group);
    all_groups_.insert(current_group);
    return 0;
}

/**
 * @brief GroupContainer::findGroup Finds a group given their name, if they exist in the container.
 * @param group_id The name of the group to be found.
 * @return A pointer to the group if successfully found, otherwise a nullptr.
 */
Group* GroupContainer::findGroup(int group_id)
{
    std::unordered_map<int, Group*>::const_iterator found = all_groups_.find(group_id);

    if (found == all_groups_.end())
    {
        return nullptr;
    }

    return found->second;
}

/**
 * @brief GroupContainer::addGroup Add a group to the container if they already are not in it.
 * @param group A pointer to the group to be added to the container.
 * @return True if successfully added, false if they already are in the container.
 */
bool GroupContainer::addGroup(Group* group) {
        std::pair<int, Group*> current_group (group->getID(), group);
        all_groups_.insert(current_group);
        return true;
}

bool GroupContainer::addUser(User *user, int group_id) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in GroupContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    findGroup(group_id)->addMember(user);

    std::string sqlRequest = "UPDATE groups SET members =\"" + all_groups_.at(group_id)->getMemberString() + "\" WHERE id = " + std::to_string(group_id) + ";";
    const char *sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackUpdateGroups, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db_);
        return false;
    }else{
        //fprintf(stdout, "Operation done successfully\n");
        sqlite3_close(db_);
        return true;
    }
}

/**
 * @brief GroupContainer::removeUser Removes a user from the specified group.
 * @param user The user that will be removed from the group.
 * @param group_id The id of the group that the user will be removed from.
 * @return True if the user is removed, False if not.
 */
bool GroupContainer::removeUser(User *user, int group_id) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in GroupContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    findGroup(group_id)->removeMember(user);

    std::string sqlRequest = "UPDATE groups SET members =" + findGroup(group_id)->getMemberString();
    const char *sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackUpdateGroups, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db_);
        return false;
    }else{
        //fprintf(stdout, "Operation done successfully\n");
        sqlite3_close(db_);
        return true;
    }
}

int GroupContainer::callbackUpdateGroups(void *data, int argc, char **argv, char **azColName) {
    return 0;
}
