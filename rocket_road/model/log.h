#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>

class Log {

    std::fstream outputFile;

public:
    Log();
    ~Log();

    void exit();
    Log& operator<<(const std::string str);
};

#endif // LOG_H
