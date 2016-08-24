#include "post.h"

/**
 * @brief Post::Post Constructor of post for when a post is retrieved from the database.
 * @param poster A pointer to the user who posted the post.
 * @param post The text of the post.
 * @param timestamp The time the post was posted, in the format "YYYY-MM-DD HH:MM:SS".
 * @param comments A vector of pointers to comment objects for the post
 */
Post::Post(User* poster, std::string post, std::string timestamp, std::string likes, std::string post_id)
{
    timestamp_ = timestamp;
    poster_ = poster;
    post_ = post;
    likes_string_ = likes;
    post_id_ = post_id;

    std::vector<std::string> vect;
    std::vector<User*> users;

    std::stringstream ss(likes);
    std::string item;

    while (std::getline(ss, item, ',')) {
            vect.push_back(item);
    }

}

/**
 * @brief Post::Post Constructor for a post object where a user is adding a post. Timestamps the post.
 * @param poster A pointer to the user who posted the post.
 * @param post The text of the post.
 */
Post::Post(User *poster, std::string post) {
    Date* timestamp = new Date();
    timestamp_ = timestamp->getDateAndTime();
    poster_ = poster;
    post_ = post;
}

/**
 * @brief Post::getPoster Getter to retrieve the poster.
 * @return A pointer to the poster.
 */
User * Post::getPoster()
{
    return poster_;
}

/**
 * @brief Post::getTime A getter to retrieve the time of the post.
 * @return The time of the post, in the format "YYYY-MM-DD HH:MM:SS".
 */
std::string Post::getTime()
{
    return timestamp_;
}

/**
 * @brief Post::getPost Getter to retrieve the post content.
 * @return The post content.
 */
std::string Post::getPost()
{
    return post_;
}

/**
 * @brief Post::likedBy Returns whether or not the specified user has liked the post.
 * @param liker User that may or may not have liked the post
 * @return True if the user liked the post, False if not.
 */
bool Post::likedBy(User *liker)
{
    if (likes_string_.find(liker->getUserName()) != std::string::npos)
       return true;
    else
       return false;
}

/**
 * @brief Post::hasLikes Whether or not a user has liked the post.
 * @return True if post has likes, false if not.
 */
bool Post::hasLikes()
{
    if (likes_string_.size() > 0)
    {
        return true;
    } else
    {
        return false;
    }
}

/**
 * @brief Post::setLikesString Sets the string of who liked the post.
 * @param likes The new string of people who liked the post.
 * @return Returns true if the string is changed.
 */
bool Post::setLikesString(std::string likes) {
    likes_string_ = likes;
    return true;
}

/**
 * @brief Post::getLikesString Gets the string of who liked the post.
 * @return The string containing the names of users who liked the post.
 */
std::string Post::getLikesString() {
    return likes_string_;
}

/**
 * @brief Post::getPostID Retrieves the id of the post.
 * @return The id of the post.
 */
std::string Post::getPostID() {
    return post_id_;
}

/**
 * @brief Post::setID Sets the id of the post.
 * @param post_id The id that the post will be given.
 * @return True if the new id is set.
 */
bool Post::setID(std::string post_id) {
    post_id_ = post_id;
    return true;
}

/**
 * @brief Post::getComments Returns the vector of all comments on the post.
 * @return A vector of the pointers to all comments on the post.
 */
std::vector<Comment*> Post::getComments()
{
    return comments_;
}

/**
 * @brief Post::setComments Sets the comments of the post.
 * @param comments A vector of pointers to the comments on the post.
 * @return True if the original vector is changed.
 */
bool Post::setComments(std::vector<Comment*> comments) {
    comments_ = comments;
    true;
}
