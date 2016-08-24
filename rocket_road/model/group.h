#ifndef GROUP_H
#define GROUP_H

#include "user.h"

class User;

class Group
{
public:
    Group(int id, std::string name, std::string description, std::string members, std::string startDate, std::string endDate);
    ~Group();
    bool setID(int id);
    bool setName(std::string name);
    bool setDescription(std::string description);
    bool addMember(User* user);
    bool removeMember(User* user);
    bool setDate(std::string dateStart, std::string dateEnd);
    bool setLocation(std::string location);
    int getID();
    std::string getName();
    std::string getDescription();
    std::string getDate();
    std::string getLocation();
    std::string getMemberString();
    std::vector<std::string> getMembers();
private:
    int id_;
    std::string name_;
    std::string description_;
    std::string startDate_;
    std::string endDate_;
    std::string location_;
    std::string members_string_;
};

#endif // GROUP_H
