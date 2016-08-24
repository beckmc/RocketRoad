#include "date.h"

/**
 * @brief Date::Date Class constructor.
 */
Date::Date()
{
    currentDateTime();
}

/**
 * @brief Date::currentDateTime Generates the current date and time and stores it in the Date object.
 */
void Date::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format

    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    date_time_ = std::string(buf);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    date_ = std::string(buf);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    time_ = std::string(buf);
}

/**
 * @brief Date::getDateAndTime Getter to retrieve the date and time.
 * @return The date and time.
 */
std::string Date::getDateAndTime()
{
    return date_time_;
}

/**
 * @brief Date::getDate Getter to retrieve the date.
 * @return The date.
 */
std::string Date::getDate()
{
    return date_;
}

/**
 * @brief Date::getTime Getter to retrieve the time.
 * @return The time.
 */
std::string Date::getTime()
{
    return time_;
}

/**
 * @brief Date::convertDate
 * @param conversion
 * @return time month day, year
 */
std::string Date::convertDate(std::string conversion) {
    std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Sep", "Oct", "Nov", "Dec"};
    std::string date = conversion.substr(0, 10);
    std::string time = conversion.substr(11, 18);

    std::string year = date.substr(0, 4);
    std::string month = months[std::stoi(date.substr(5, 6)) - 1];
    std::string day = date.substr(8, 9);

    std::string returnValue = time + " " + month + " " + day + ", " + year;
    return returnValue;
}
