#include "user.h"

/**
 * @brief User::User Constructor for the user object. Used when loading users.
 * @param user_name The username of the user (which is the email).
 * @param email The email of the user.
 * @param first_name The first name of the user.
 * @param last_name The last name of the user.
 * @param friends A string of id's which are the user's friends.
 * @param password The user's password.
 * @param profile_picture The path of the user's profile picture.
 * @param user_ID The user's id.
 */
User::User(std::string user_name, std::string email, std::string first_name, std::string last_name, std::string groups, std::string friends, std::string password, std::string profile_picture, int user_ID)
{
    user_name_ = user_name;
    email_ = email;
    first_name_ = first_name;
    last_name_ = last_name;
    friends_ = friends;
    groups_ = groups;
    password_ = password;
    profile_picture_ = profile_picture;
    logged_in_ = false;
    user_ID_ = user_ID;
}

/**
 * @brief User::~User Class destructor
 */
User::~User() {

}

/**
 * @brief User::getName Getter to get a user's name.
 * @return The user's name, in the format of "firstname lastname"
 */
std::string User::getName()
{
    return first_name_ + " " + last_name_;
}

/**
 * @brief User::getPosters Getter to get a list of all posts a user can view.
 * @return A vector containing the id's of the user's friends and the user's id.
 */
std::vector<std::string> User::getPosters()
{
    std::vector<std::string> vect;

    vect = getFriends();

    vect.push_back(user_name_);

    return vect;
}

std::vector<std::string> User::getGroups()
{
    std::vector<std::string> vect;
    std::stringstream ss(groups_);
    std::string item;

    while(std::getline(ss, item, ','))
    {
        vect.push_back(item);
    }

    return vect;
}

/**
 * @brief User::getFriends Returns the list of friends associated with the user
 * @return A vector containg the id's of the user's friends
 */
std::vector<std::string> User::getFriends()
{
    std::vector<std::string> vect;

    std::stringstream ss(friends_);
    std::string item;
    while (std::getline(ss, item, ',')) {
            vect.push_back(item);
    }

    return vect;
}

/**
 * @brief User::addGroup Adds group to list of groups user belongs to
 * @param group The group the user is to be added to
 * @return True if successfully changed
 */
bool User::addGroup(Group* group) {
    //groups_.push_back(group);
    return true;
}

/**
 * @brief User::removeGroup Removes group from list of groups user belongs to
 * @param group The group the user is to be removed from
 * @return True if successfully removed, false if the user isn't in that group
 */
bool User::removeGroup(Group* group) {
//    for (unsigned long i = 0; i < groups_.size(); i++) {
//        if (groups_.at(i) == group) {
//            groups_.erase(groups_.begin() + i);
//            return true;
//        }
//    }
    return false;
}

bool User::isFriend(User* other_user)
{
    std::vector<std::string> friends = getFriends();
    for (unsigned int i = 0; i < friends.size(); i++)
    {
        if (other_user->getUserName().compare(friends[i]) == 0)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief User::tryPassword Compares the password given to the stored password for the user.
 * @param pass The attempted password.
 * @return True if the password is the same, false if it isn't.
 */
bool User::tryPassword(std::string pass)
{
    if (pass.compare(password_) == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/**
 * @brief User::getID Gets the ID of the user.
 * @return The User's ID.
 */
int User::getID()
{
    return user_ID_;
}

/**
 * @brief User::getUserName Gets the UserName of the user.
 * @return The Username.
 */
std::string User::getUserName()
{
    return user_name_;
}

/**
 * @brief User::addFriend Adds a friend to the current user
 * @param user Friend that will be added
 * @return returns true if the friend is added.
 */
bool User::addFriend(User *user) {
    if (friends_.size() > 0) {
        friends_ += ",";
    }
    friends_ += user->getUserName();
    return true;
}

/**
 * @brief User::removeFriend Removes a friend to the current user
 * @param user Friend that will be removed
 * @return True if the friend is removed.
 */
bool User::removeFriend(User *user) {
    if (friends_.find("," + user->getUserName()) != std::string::npos) {
        int position = friends_.find("," + user->getUserName());
        friends_.erase(position, user->getUserName().size() + 1);
    } else if (friends_.find(user->getUserName() + ",") != std::string::npos) {
        int position = friends_.find(user->getUserName() + ",");
        friends_.erase(position, user->getUserName().size() + 1);
    } else {
        int position = friends_.find(user->getUserName());
        friends_.erase(position, user->getUserName().size());
    }
    return true;
}

/**
 * @brief User::setFriendString Sets the string that stores the users friends.
 * @param new_string The string that the friends_ string will be set to.
 */
void User::setFriendString(std::string new_string)
{
    friends_ = new_string;
}

/**
 * @brief User::getFriendString Returns the string of friends.
 * @return Returns the string containing all of the user's friends.
 */
std::string User::getFriendString() {
    return friends_;
}

/**
 * @brief User::setFirstName Sets the first name of the user.
 * @param new_name The name that the user will be given.
 * @return True if the new name is set.
 */
bool User::setFirstName(std::string new_name) {
    first_name_ = new_name;
    return true;
}

/**
 * @brief User::setLastName Sets the last name of the user.
 * @param new_name The name that the user will be given.
 * @return True if the new name is set.
 */
bool User::setLastName(std::string new_name) {
    last_name_ = new_name;
    return true;
}

/**
 * @brief User::setPassword Sets a new password for the user.
 * @param new_pass The password that the user is changing to.
 * @return True if the password is changed.
 */
bool User::setPassword(std::string new_pass) {
    password_ = new_pass;
    return true;
}

/**
 * @brief User::isMember Returns whether or not a user has joined the specified group.
 * @param groupID The groupID that the user may or may not be a member of.
 * @return True if the user is a member of the group. False if the user is not a member of the group.
 */
bool User::isMember(std::string groupID) {
    if (groups_.find(groupID) != std::string::npos) {
        return true;
    }

    return false;
}
