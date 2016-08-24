#ifndef SIGNUP_H
#define SIGNUP_H

#include <string>
#include <stdio.h>
#include <sqlite3.h>

class Signup
{
public:
    Signup();
    bool addUser(std::string email, std::string first_name, std::string last_name, std::string password);
private:
    sqlite3 *db_;
    static int callback(void *data, int argc, char **argv, char **azColName);
};

#endif // SIGNUP_H
