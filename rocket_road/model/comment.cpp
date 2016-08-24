#include "comment.h"

/**
 * @brief Comment::Comment Constructor for a comment object. Used when loading a comment from the database
 * @param poster The user who posted the comment.
 * @param post The text of the comment.
 * @param timestamp The time the comment was posted, in the format "YYYY-MM-DD HH:MM:SS".
 */
Comment::Comment(User* poster, std::string post, std::string timestamp)
{
    timestamp_ = timestamp;
    poster_ = poster;
    post_ = post;
}

/**
 * @brief Comment::Comment Constructor for a comment object where a user is adding a comment. Timestamps the comment.
 * @param poster The user who is posting the comment.
 * @param post The text of the comment.
 */
Comment::Comment(User* poster, std::string post)
{
    Date* timestamp = new Date();
    timestamp_ = timestamp->getDateAndTime();
    poster_ = poster;
    post_ = post;
}

/**
 * @brief Comment::getPoster Getter to retrieve the poster of the comment.
 * @return A pointer to the user who posted the comment.
 */
User * Comment::getPoster()
{
    return poster_;
}

/**
 * @brief Comment::getTime Getter to retrieve the timestamp of the comment.
 * @return The timestamp, in the format "YYYY-MM-DD HH:MM:SS".
 */
std::string Comment::getTime()
{
    return timestamp_;
}

/**
 * @brief Comment::getPost Getter to retrieve the text of the comment.
 * @return The text of the comment.
 */
std::string Comment::getPost()
{
    return post_;
}
