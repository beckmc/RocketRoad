#include "search.h"

std::vector<User*> Search::return_users_;
UserContainer* Search::user_container_;

/**
 * @brief Search::Search Basic constructor.
 * @param user_container The container of all users.
 */
Search::Search(UserContainer *user_container)
{
    user_container_ = user_container;
}

/**
 * @brief Search::findUser Returns the list of all users containing the search phrase.
 * @param searchPhrase The phrase that is being searched for.
 * @return The vector of all users that contain the searchPhrase.
 */
std::vector<User*> Search::findUser(std::string searchPhrase) {
    return_users_.clear();

    std::vector<std::string> phrases;
    std::stringstream ss(searchPhrase);
    std::string item;
    while (std::getline(ss, item, ' ')) {
            phrases.push_back(item);
    }


    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in PostContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string sqlRequest = "SELECT * FROM users where ";

    for (int i = 0; i < phrases.size(); i++) {
        if (i > 0) {
            sqlRequest += " or ";
        }
        sqlRequest += "firstName like \"%" + phrases.at(i) + "%\" or ";
        sqlRequest += "lastName like \"%" + phrases.at(i) + "%\" or ";
        sqlRequest += "email like \"%" + phrases.at(i) + "%\"";
    }

    sqlRequest += ";";

    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackFindUsers, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db_);
    return return_users_;
}

/**
 * @brief Search::callbackFindUsers Callback function for finding users. Retrives users
 * from the database and adds the users retrieved to the return vector.
 */
int Search::callbackFindUsers(void *data, int argc, char **argv, char **azColName) {
    User* user = user_container_->findUser(argv[1]);
    return_users_.push_back(user);
    return 0;
}

