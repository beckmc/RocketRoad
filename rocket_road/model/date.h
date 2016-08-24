#ifndef DATE_H
#define DATE_H
#include <string>
#include <time.h>
#include <vector>
#include <sstream>

class Date
{
public:
    Date();
    std::string getTime();
    std::string getDateAndTime();
    std::string getDate();
    std::string convertDate(std::string date);
private:
    void currentDateTime();
    std::string date_time_;
    std::string time_;
    std::string date_;
};

#endif // DATE_H
