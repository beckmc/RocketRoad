#include "commentcontainer.h"

std::vector<Comment*> CommentContainer::comment_vector_;
Post* CommentContainer::post_;
UserContainer* CommentContainer::user_container_;

/**
 * @brief CommentContainer::CommentContainer Basic Constructor that pulls all comment data from the database for the specified post.
 * @param post The post that the comments are being loaded from.
 * @param user_container The container of all users.
 */
CommentContainer::CommentContainer(Post* post, UserContainer* user_container)
{
    post_ = post;
    user_container_ = user_container;
    comment_vector_.clear();
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        mvprintw(10, 10, "Can't open database in CommentContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //printw("Opened database successfully\n");
    }

    std::string sqlRequest = "SELECT * FROM comments where postID = \"" + post_->getPostID() + "\";";
    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackPopulateComments, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        //printw("SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stderr, sql);
        //printw("Operation done successfully\n");
    }
    sqlite3_close(db_);
}

/**
 * @brief CommentContainer::CommentContainer Constructor pulling all group comment data from the database.
 * @param post The post that the data is being loaded from
 * @param user_container The container of all users.
 * @param isGroupComment Whether or not the comment is a group comment or not.
 */
CommentContainer::CommentContainer(Post *post, UserContainer *user_container, int isGroupComment) {
    post_ = post;
    user_container_ = user_container;
    comment_vector_.clear();
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        mvprintw(10, 10, "Can't open database in CommentContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //printw("Opened database successfully\n");
    }

    std::string sqlRequest = "SELECT * FROM groupComments where postID = \"" + post_->getPostID() + "\";";
    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackPopulateComments, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        //printw("SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stderr, sql);
        //printw("Operation done successfully\n");
    }
    sqlite3_close(db_);

}

/**
 * @brief CommentContainer::callbackPopulateComments Callback function for commenting. Retrieves data from
 * the database and generates the comment objects.
 */
int CommentContainer::callbackPopulateComments(void *data, int argc, char **argv, char **azColName){
    printw("populating\n");
    int i;
    std::string posterUsername = "";
    std::string content = "";
    std::string timestamp = "";
    for(i=1; i<argc; i++){
        switch(i)
        {
        case 2:
            posterUsername = argv[i];
            break;
        case 3:
            content = argv[i];
            break;
        case 4:
            timestamp = argv[i];
            break;
        }
    }

    Comment* comment = new Comment(user_container_->findUser(posterUsername), content, timestamp);
    comment_vector_.push_back(comment);
    return 0;
}

/**
 * @brief CommentContainer::getComments Retrieves the list of comments.
 * @return A vector containing pointers to all comments on the specified post.
 */
std::vector<Comment*> CommentContainer::getComments() {
    return comment_vector_;
}

/**
 * @brief CommentContainer::send_comment Sends a comment to the data base for the specified post.
 * @param content The contents of the comment.
 * @param user The user that made the comment
 * @param postID The id of the post that is commented on.
 * @return True if the comment is sent, False if not.
 */
bool CommentContainer::send_comment(std::string content, User *user, std::string postID) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        //exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    Comment* comment = new Comment(user, content);

    std::string sqlRequest = "INSERT INTO comments (postID, posterUsername, comment, timestamp) values (\"" + postID  + "\", \"" + user->getUserName()  + "\", \"" + content + "\", \"" + comment->getTime() + "\");";
    const char *sql = sqlRequest.c_str();
    code = sqlite3_exec(db_, sql, callbackWriteComment, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        //printw("SQL error: %s\n", zErrMsg);
        sqlite3_close(db_);
        return false;
        sqlite3_free(zErrMsg);
    }else{
        comment_vector_.push_back(comment);
        sqlite3_close(db_);
        printw("Operation done successfully\n");
        return true;
    }

    sqlite3_close(db_);
    return true;
}

/**
 * @brief CommentContainer::send_comment_group Sends a comment to the data base for the specified post in a group.
 * @param content The contents of the comment.
 * @param user The user making the comment.
 * @param postID The id of the post that is being commented on.
 * @return True if the comment is sent, False if not.
 */
bool CommentContainer::send_comment_group(std::string content, User *user, std::string postID) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        //exit(0);
    }else{
        //fprintf(stderr, "Opened database successfully\n");
    }

    Comment* comment = new Comment(user, content);

    std::string sqlRequest = "INSERT INTO groupComments (postID, posterUsername, comment, timestamp) values (\"" + postID  + "\", \"" + user->getUserName()  + "\", \"" + content + "\", \"" + comment->getTime() + "\");";
    const char *sql = sqlRequest.c_str();
    code = sqlite3_exec(db_, sql, callbackWriteComment, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        //printw("SQL error: %s\n", zErrMsg);
        sqlite3_close(db_);
        return false;
        sqlite3_free(zErrMsg);
    }else{
        comment_vector_.push_back(comment);
        sqlite3_close(db_);
        printw("Operation done successfully\n");
        return true;
    }

    sqlite3_close(db_);
    return true;
}

int CommentContainer::callbackWriteComment(void *data, int argc, char **argv, char **azColName) {
    return 0;
}
