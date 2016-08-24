#include "signup.h"

/**
 * @brief Signup::Signup Class constructor.
 */
Signup::Signup() {
}

/**
 * @brief Signup::addUser Function to add a user to the network. Fails if the username is already taken.
 * @param email The email/username of the user.
 * @param first_name The user's first name.
 * @param last_name The user's last name.
 * @param password The user's password.
 * @return True if the user is added, false if the username is already taken.
 */
bool Signup::addUser(std::string email, std::string first_name, std::string last_name, std::string password)
{
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in Signup: %s\n", sqlite3_errmsg(db_));
        //exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    std::string sqlRequest = "INSERT INTO users (email, firstName, lastName, password) values (\"" + email  + "\", \"" + first_name + "\", \"" + last_name + "\", \"" + password + "\")";
    const char *sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callback, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        sqlite3_close(db_);
        return false;
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
    return true;
}

/**
 * @brief Signup::callback Callback function for signup.
 */
int Signup::callback(void *NotUsed, int argc, char **argv, char **azColName){
   return 0;
}
