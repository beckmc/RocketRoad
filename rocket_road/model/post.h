#ifndef POST_H
#define POST_H

#include "date.h"
#include "user.h"
#include "comment.h"
#include <algorithm>

class Post
{
public:
    Post(User* poster, std::string post, std::string timestamp, std::string likes, std::string post_id);
    Post(User* poster, std::string post);
    User * getPoster();
    std::string getTime();
    std::string getPost();
    std::vector<std::string> getLikes();
    std::vector<Comment*> getComments();
    bool setComments(std::vector<Comment*> comments);
    std::string getLikesString();
    bool setLikesString(std::string likes);
    bool setID(std::string post_id);
    bool hasLikes();
    bool likedBy(User* liker);
    std::string getPostID();
private:
    std::string timestamp_;
    User * poster_;
    std::string post_;
    std::string post_id_;
    std::string likes_string_;
    std::vector<Comment*> comments_;

};

#endif // POST_H
