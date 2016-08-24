#include "log.h"

/**
 * @brief Log::Log Basic Constructor
 */
Log::Log() {
    outputFile.open("log.txt", std::fstream::out | std::fstream::app);
}

/**
 * @brief Log::~Log Basic Destructor
 */
Log::~Log() {
    outputFile.close();
}

/**
 * @brief Log::operator << Override function to allow for log printing.
 * @param logText The text that will be printed.
 * @return A pointer to this log.
 */
Log& Log::operator<<(std::string logText) {
    outputFile << logText
               << std::endl;

    return *this;
}
