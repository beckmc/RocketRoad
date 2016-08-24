#include "message.h"

/**
 * @brief Message::Message Basic constructor with timestamp given.
 * @param toUser User that the message will be sent to.
 * @param fromUser User that the message is being sent from.
 * @param message The message that the fromUser is sending.
 * @param timestamp The time and date that the message was sent.
 */
Message::Message(User *toUser, User *fromUser, std::string message, std::string timestamp)
{
    toUser_ = toUser;
    fromUser_ = fromUser;
    message_ = message;
    timestamp_ = timestamp;
}

/**
 * @brief Message::Message Basic constructor without a given timestamp.
 * @param toUser User that the message will be sent to.
 * @param fromUser User that the message is being sent from.
 * @param message The message that the fromUser is sending.
 */
Message::Message(User *toUser, User *fromUser, std::string message)
{
    toUser_ = toUser;
    fromUser_ = fromUser;
    message_ = message;
    Date* timestamp = new Date();
    timestamp_ = timestamp->getDateAndTime();
}

/**
 * @brief Message::getToUser Retrieves the user that is recieveing the message
 * @return User that is recieving the message.
 */
User* Message::getToUser() {
    return toUser_;
}

/**
 * @brief Message::getFromUser Retrieves the user that is sending the message
 * @return User that is sending the message.
 */
User* Message::getFromUser() {
    return fromUser_;
}

/**
 * @brief Message::getTime Gets the date and time the message was sent.
 * @return The date and time the message was send
 */
std::string Message::getTime() {
    return timestamp_;
}

/**
 * @brief Message::getMessage Retrieves the contents of the message
 * @return The contents of the message.
 */
std::string Message::getMessage() {
    return message_;
}
