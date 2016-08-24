#include "group.h"

/**
 * @brief Group::Group Class constructor.
 */
Group::Group(int id, std::string name, std::string description, std::string members, std::string startDate, std::string endDate)
{
    id_ = id;
    name_ = name;
    description_ = description;
    members_string_ = members;
    startDate_ = startDate;
    endDate_ = endDate;
}

/**
 * @brief Group::~Group Class destructor.
 */
Group::~Group() {

}

/**
 * @brief Group::setID Set the id of the group.
 * @param id The id of the group.
 * @return True if set.
 */
bool Group::setID(int id) {
    id_ = id;
    return true;
}

/**
 * @brief Group::setName Set the name of the group.
 * @param name The name of the group.
 * @return True if set.
 */
bool Group::setName(std::string name) {
    name_ = name;
    return true;
}

/**
 * @brief Group::setDescription Set the description of the group.
 * @param description The description/information about the group.
 * @return True if set.
 */
bool Group::setDescription(std::string description) {
    description_ = description;
    return true;
}

/**
 * @brief Group::addMember Add a member to the group.
 * @param user A pointer to the user to be added.
 * @return True if successfully added to the group.
 */
bool Group::addMember(User* user) {
    if (members_string_.size() > 0) {
        members_string_ += ",";
    }
    members_string_ += user->getUserName();
    return true;
}

/**
 * @brief Group::removeMember Searches to see if a user is a member of a group, and if so, removes them.
 * @param user A pointer to the user to be removed.
 * @return True if the user is in the group and removed, otherwise false.
 */
bool Group::removeMember(User* user) {
    if (members_string_.find("," + user->getUserName()) != std::string::npos) {
        int position = members_string_.find("," + user->getUserName());
        members_string_.erase(position, user->getUserName().size() + 1);
    } else if (members_string_.find(user->getUserName() + ",") != std::string::npos) {
        int position = members_string_.find(user->getUserName() + ",");
        members_string_.erase(position, user->getUserName().size() + 1);
    } else {
        int position = members_string_.find(user->getUserName());
        members_string_.erase(position, user->getUserName().size());
    }
    return true;
}

/**
 * @brief Group::setDate Set the date of the trip the group made.
 * @param dateStart The start date of the trip.
 * @param dateEnd The end date of the trip.
 * @return True if successfully set.
 */
bool Group::setDate(std::string dateStart, std::string dateEnd) {
    startDate_ = dateStart;
    endDate_ = dateEnd;

    return true;
}

/**
 * @brief Group::setLocation Set the location of the trip.
 * @param location The location of the trip.
 * @return True if successfully set.
 */
bool Group::setLocation(std::string location) {
    location_ = location;

    return true;
}

/**
 * @brief Group::getID A getter to get the id of the group.
 * @return The id of the group.
 */
int Group::getID() {
    return id_;
}

/**
 * @brief Group::getName A getter to get the name of the group.
 * @return The name of the group.
 */
std::string Group::getName() {
    return name_;
}

/**
 * @brief Group::getDescription A getter to get the description of the group.
 * @return The description of the group.
 */
std::string Group::getDescription() {
    return description_;
}

/**
 * @brief Group::getDate Getter to get the start and end dates of the group's trip.
 * @return The dates, in the format of startdate-enddate.
 */
std::string Group::getDate() {
    return startDate_ + "-" + endDate_;
}

/**
 * @brief Group::getLocation Getter to get the location of the group's trip.
 * @return The location of the group's trip.
 */
std::string Group::getLocation() {
    return "New Mexico";
}

std::string Group::getMemberString() {
    return members_string_;
}

/**
 * @brief Group::getMembers Getter to get the members of the group.
 * @return A vector containing pointers to the members of the group.
 */
std::vector<std::string> Group::getMembers() {

    std::vector<std::string> vect;

    std::stringstream ss(members_string_);
    std::string item;
    while (std::getline(ss, item, ',')) {
            vect.push_back(item);
    }

    return vect;
}
