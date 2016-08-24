#ifndef MESSAGECONTAINER_H
#define MESSAGECONTAINER_H

#include "message.h"
#include "usercontainer.h"
#include "user.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

class MessageContainer
{
public:
    MessageContainer(UserContainer *userContainer, User *user1, User *user2);
    std::vector<Message*> get_messages();
    bool send_message(User* toUser, User* fromUser, std::string messageText);
private:
    sqlite3 *db_;
    static UserContainer* user_container_;
    static std::vector<Message*> messages_;
    static int callbackPopulateMessages(void *data, int argc, char **argv, char **azColName);
    static int callbackSendMessage(void *data, int argc, char **argv, char **azColName);
};

#endif // MESSAGECONTAINER_H
