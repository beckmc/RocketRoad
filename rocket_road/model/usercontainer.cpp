#include "usercontainer.h"

std::unordered_map<std::string, User*> UserContainer::all_users_;

/**
 * @brief UserContainer::UserContainer Class constructor. Loads all users from the database into the program.
 */
UserContainer::UserContainer()
{
    all_users_.clear();
    int code;
    char *sql;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in UserContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    sql = "SELECT * FROM users";

    code = sqlite3_exec(db_, sql, callbackPopulateUsers, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}

/**
 * @brief UserContainer::callbackPopulateUsers Callaback function to load users.
 */
int UserContainer::callbackPopulateUsers(void *data, int argc, char **argv, char **azColName){
    int i;
    int id = 0;
    std::string idString;
    std::string email = "";
    std::string fname = "";
    std::string lname = "";
    std::string password = "";
    std::string groups = "";
    std::string friends = "";
    std::string picture = "";
    for(i=0; i<argc; i++){
        switch(i)
        {
        case 0:
            idString = argv[i];
            id = std::stoi(idString);
            break;
        case 1:
            email = argv[i];
            break;
        case 2:
            fname = argv[i];
            break;
        case 3:
            lname = argv[i];
            break;
        case 4:
            password = argv[i];
            break;
        case 5:
            groups = argv[i] ? argv[i] : "";
            break;
        case 6:
            friends = argv[i] ? argv[i] : "";
            break;
        case 7:
            picture = argv[i] ? argv[i] : "";
            break;
        }
    }
    User* user = new User(email, email, fname, lname, groups, friends, password, picture, id);
    std::pair<std::string, User*> current_user (user->getUserName(), user);
    all_users_.insert(current_user);
    return 0;
}

/**
 * @brief UserContainer::get Get a user from the database and add them to the user container.
 * @param email The email of the user to be retrieved from the database.
 * @return True if successfully loaded.
 */
bool UserContainer::get(std::string email) {
    int code;
    const char *sql;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    std::string sqlRequest = "SELECT * FROM users where email = \"" + email + "\"";
    sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackPopulateUsers, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        sqlite3_close(db_);
        return false;
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        return true;
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}


/**
 * @brief UserContainer::findUser Finds a user given their user ID, if they exist in the container.
 * @param user_id The user ID of the user to be found.
 * @return A pointer to the user if successfully found, otherwise a nullptr.
 */
User* UserContainer::findUser(std::string user_id)
{
    std::unordered_map<std::string, User*>::const_iterator found = all_users_.find(user_id);

    if (found == all_users_.end())
    {
        return nullptr;
    }

    return found->second;
}

/**
 * @brief UserContainer::addUser Add a user to the container.
 * @param user A pointer to the user to be added to the container.
 * @return True if successfully added, false if they already are in the container.
 */
bool UserContainer::addUser(User* user) {
    std::pair<std::string, User*> current_user (user->getUserName(), user);
    all_users_.insert(current_user);
    return true;
}

bool UserContainer::addFriend(User *user1, User *user2) {
    bool user1ContainsUser2 = false;
    bool user2ContainsUser1 = false;

    if(user1->getFriendString().find(user2->getUserName()) != std::string::npos) {
        user1ContainsUser2 = true;
    }
    if(user2->getFriendString().find(user1->getUserName()) != std::string::npos) {
        user2ContainsUser1 = true;
    }

    if (user1ContainsUser2 && user2ContainsUser1) {
        //both users have each other on their friend lists
        return true;
    } else if (user1ContainsUser2) {
        //user 1 has user 2 on their friend list
        user2->addFriend(user1);
        updateInformation("UPDATE users SET friends = '" + user2->getFriendString() + "' where email = '" + user2->getUserName() + "';");
    } else if (user2ContainsUser1) {
        //user 2 has user 1 on their friend list
        user1->addFriend(user2);
        updateInformation("UPDATE users SET friends = '" + user1->getFriendString() + "' where email = '" + user1->getUserName() + "';");
    } else {
        //neither users have each other on their friend list
        user1->addFriend(user2);
        user2->addFriend(user1);
        updateInformation("UPDATE users SET friends = '" + user1->getFriendString() + "' where email = '" + user1->getUserName() + "';");
        updateInformation("UPDATE users SET friends = '" + user2->getFriendString() + "' where email = '" + user2->getUserName() + "';");
    }
}

bool UserContainer::removeFriend(User *user1, User *user2) {
    bool user1ContainsUser2 = false;
    bool user2ContainsUser1 = false;

    if(user1->getFriendString().find(user2->getUserName()) != std::string::npos) {
        user1ContainsUser2 = true;
    }
    if(user2->getFriendString().find(user1->getUserName()) != std::string::npos) {
        user2ContainsUser1 = true;
    }

    if (user1ContainsUser2 && user2ContainsUser1) {
        //both users have each other on their friend lists
        user1->removeFriend(user2);
        user2->removeFriend(user1);
        updateInformation("UPDATE users SET friends = '" + user1->getFriendString() + "' where email = '" + user1->getUserName() + "';");
        updateInformation("UPDATE users SET friends = '" + user2->getFriendString() + "' where email = '" + user2->getUserName() + "';");
    } else if (user1ContainsUser2) {
        //user 1 has user 2 on their friend list
        user1->removeFriend(user2);
        updateInformation("UPDATE users SET friends = '" + user1->getFriendString() + "' where email = '" + user1->getUserName() + "';");
    } else if (user2ContainsUser1) {
        //user 2 has user 1 on their friend list
        user2->removeFriend(user1);
        updateInformation("UPDATE users SET friends = '" + user2->getFriendString() + "' where email = '" + user2->getUserName() + "';");
    } else {
        //neither users have each other on their friend list
        return true;
    }
}

bool UserContainer::editFirstName(User* user, std::string new_name) {
    updateInformation("UPDATE users SET firstName = '" + new_name + "' where email = '" + user->getUserName() + "';");
    user->setFirstName(new_name);
}

bool UserContainer::editLastName(User* user, std::string new_name) {
    updateInformation("UPDATE users SET lastName = '" + new_name + "' where email = '" + user->getUserName() + "';");
    user->setLastName(new_name);
}

bool UserContainer::editPassword(User* user, std::string new_pass) {
    updateInformation("UPDATE users SET password = '" + new_pass + "' where email = '" + user->getUserName() + "';");
    user->setPassword(new_pass);
}

void UserContainer::updateInformation(std::string sql_request) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }
    const char* sql = sql_request.c_str();

    code = sqlite3_exec(db_, sql, callbackUpdateUser, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        sqlite3_close(db_);
        //return false;
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        //return true;
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}

int UserContainer::callbackUpdateUser(void *data, int argc, char **argv, char **azColName){
    return 0;
}
