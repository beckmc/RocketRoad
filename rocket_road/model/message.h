#ifndef MESSAGE_H
#define MESSAGE_H

#include "user.h"
#include "date.h"

class Message
{
public:
    Message(User* toUser, User* fromUser, std::string message, std::string timestamp);
    Message(User *toUser, User *fromUser, std::string message);
    User * getToUser();
    User * getFromUser();
    std::string getTime();
    std::string getMessage();
private:
    std::string timestamp_;
    std::string message_;
    User* toUser_;
    User* fromUser_;
};

#endif // MESSAGE_H
