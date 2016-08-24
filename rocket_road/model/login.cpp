#include "login.h"

/**
 * @brief Login::Login Class constructor.
 */
Login::Login()
{
    user_container_ = new UserContainer();
}

/**
 * @brief Login::Login Class constructor.
 * @param user_container
 */
Login::Login(UserContainer * user_container)
{
    user_container_ = user_container;
}

/**
 * @brief Login::operator = Operator overload to set two login objects equal to each other.
 * @param other The other login object.
 */
void Login::operator =(Login &other)
{
    user_container_ = other.getContainer();
}

/**
 * @brief Login::testUsername Check to see if a username exists.
 * @param input The username to be tested.
 * @return True if the user exists, otherwise false.
 */
bool Login::testUsername(std::string input)
{
    if (user_container_->findUser(input) == nullptr) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Login::testPassword Check to see if the correct password is being given for a user.
 * @param user The user whose password is being checked.
 * @param input The password to be checked.
 * @return True if the password matches, otherwise false.
 */
bool Login::testPassword(User * user, std::string input)
{
    std::string username = user->getUserName();
    if (user_container_->findUser(username)->tryPassword(input)) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Login::getContainer Getter to retrieve the user container being used by the class.
 * @return A pointer to the user container being used by the class.
 */
UserContainer* Login::getContainer()
{
    return user_container_;
}

/**
 * @brief Login::loadUser Retrieves a user given their username.
 * @param input The username of the user to be found.
 * @return A pointer to the user.
 */
User * Login::loadUser(std::string input)
{
    return user_container_->findUser(input);
}

