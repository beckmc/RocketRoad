#ifndef COMMENT_H
#define COMMENT_H

#include "user.h"
#include "date.h"
#include <string>

class Comment
{
public:
    Comment(User* poster, std::string post, std::string timestamp);
    Comment(User* poster, std::string post);
    User * getPoster();
    std::string getTime();
    std::string getPost();
private:
    User* poster_;
    std::string timestamp_;
    std::string post_;
};

#endif // COMMENT_H
