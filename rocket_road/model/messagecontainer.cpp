#include "messagecontainer.h"

std::vector<Message*> MessageContainer::messages_;
UserContainer* MessageContainer::user_container_;

/**
 * @brief MessageContainer::MessageContainer Basic Constructor
 * @param userContainer The container of all users.
 * @param user1 The first user in the message.
 * @param user2 The second user in the message.
 */
MessageContainer::MessageContainer(UserContainer* userContainer, User* user1, User* user2)
{
    messages_.clear();
    user_container_ = userContainer;
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in MessageContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string sqlRequest = "SELECT * FROM messages where (toUser = \"" + user1->getUserName() + "\" AND fromUser = \"" + user2->getUserName() + "\") OR (toUser = \"" + user2->getUserName() + "\" AND fromUser = \"" + user1->getUserName() + "\")";
    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackPopulateMessages, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db_);
}

/**
 * @brief MessageContainer::callbackPopulateMessages Callback function for messaging. Retrieves data from
 * the database and generates the messages between the two users.
 */
int MessageContainer::callbackPopulateMessages(void *data, int argc, char **argv, char **azColName) {
    int i;
    std::string toUserName = "";
    std::string fromUserName = "";
    std::string content = "";
    std::string timestamp = "";
    for(i=0; i<argc; i++){
        switch(i)
        {
        case 1:
            toUserName = argv[i];
            break;
        case 2:
            fromUserName = argv[i];
            break;
        case 3:
            content = argv[i];
            break;
        case 4:
            timestamp = argv[i];
            break;
        }
    }

    Message* message = new Message(user_container_->findUser(toUserName), user_container_->findUser(fromUserName), content, timestamp);
    messages_.push_back(message);
    return 0;
}

/**
 * @brief MessageContainer::send_message Sends a message from user to the next.
 * @param toUser The user that will recieve the message.
 * @param fromUser The user that sent the message.
 * @param messageText The contents of the message.
 * @return True if the user recieves the message, False if they do not.
 */
bool MessageContainer::send_message(User *toUser, User *fromUser, std::string messageText) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        //exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    Message* message = new Message(toUser, fromUser, messageText);

    std::string sqlRequest = "INSERT INTO messages (toUser, fromUser, message, timestamp) values (\"" + toUser->getUserName()  + "\", \"" + fromUser->getUserName()  + "\", \"" + messageText + "\", \"" + message->getTime() + "\")";
    const char *sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackSendMessage, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        sqlite3_close(db_);
        return false;
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        messages_.push_back(message);
        //fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db_);
    return true;
}

int MessageContainer::callbackSendMessage(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

/**
 * @brief MessageContainer::get_messages Retrieves the messages between the two users.
 * @return The messages between the two users specified.
 */
std::vector<Message*> MessageContainer::get_messages() {
    return messages_;
}
