#include "postcontainer.h"

std::vector<Post*> PostContainer::posts_;
UserContainer * PostContainer::user_container_;
/**
 * @brief PostContainer::PostContainer Class constructor. Loads all posts one user should be able to see.
 * @param posterIDs The id's of the posts to be loaded.
 * @param user_container A pointer to the active user container.
 */
PostContainer::PostContainer(std::vector<std::string> posterIDs, UserContainer *user_container)
{
    posts_.clear();
    user_container_ = user_container;
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in PostContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string sqlRequest = "SELECT * FROM posts where posterUsername in (\"";

    for (int i = 0; i < posterIDs.size(); i++) {
        if (i > 0) {
            sqlRequest += ", \"";
        }

        sqlRequest += posterIDs.at(i) + "\"";
    }

    sqlRequest += ");";

    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackPopulatePosts, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db_);
}

/**
 * @brief PostContainer::PostContainer Constructor for the posts in a group.
 * @param group_id The id of the group that posts will be loaded from.
 */
PostContainer::PostContainer(std::string group_id)
{
    posts_.clear();
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database in PostContainer: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string sqlRequest = "SELECT * FROM groupPosts where groupID = \"" + group_id + "\";";

    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackPopulateGroupPosts, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
    }else{
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db_);
}


/**
 * @brief PostContainer::callbackPopulatePosts Callback function for posting. Retrieves data from database
 * and creates post object.
 */
int PostContainer::callbackPopulatePosts(void *data, int argc, char **argv, char **azColName){
    int i;
    std::string postID = "";
    std::string posterUsername = "";
    std::string content = "";
    std::string timestamp = "";
    std::string likes = "";
    for(i=0; i<argc; i++){
        switch(i)
        {
        case 0:
            postID = argv[i];
            break;
        case 1:
            posterUsername = argv[i];
            break;
        case 2:
            content = argv[i];
            break;
        case 3:
            timestamp = argv[i];
            break;
        case 4:
            likes = argv[i] ? argv[i] : "";
            break;
        }
    }

    Post* post = new Post(user_container_->findUser(posterUsername), content, timestamp, likes, postID);
    posts_.push_back(post);
    return 0;
}

int PostContainer::callbackPopulateGroupPosts(void *data, int argc, char **argv, char **azColName){
    int i;
    std::string postID = "";
    std::string posterUsername = "";
    std::string content = "";
    std::string timestamp = "";
    std::string likes = "";
    for(i=0; i<argc; i++){
        switch(i)
        {
        case 0:
            postID = argv[i];
            break;
        case 2:
            posterUsername = argv[i];
            break;
        case 3:
            content = argv[i];
            break;
        case 4:
            timestamp = argv[i];
            break;
        case 5:
            likes = argv[i] ? argv[i] : "";
            break;
        }
    }

    Post* post = new Post(user_container_->findUser(posterUsername), content, timestamp, likes, postID);
    posts_.push_back(post);
    return 0;
}

/**
 * @brief PostContainer::get_posts Getter to retrieve the posts.
 * @return A vector containing pointers to all posts.
 */
std::vector<Post*> PostContainer::get_posts() {
    return posts_;
}

bool PostContainer::like_post(Post *post, User* user) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string likes_string = post->getLikesString();

    if (likes_string.size() == 0) {
        likes_string += user->getUserName();
    } else {
        likes_string += "," + user->getUserName();
    }
    post->setLikesString(likes_string);
    std::string sqlRequest = "UPDATE posts SET likeIDs = '" + likes_string + "' where timestamp = '" + post->getTime() + "';";
    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackWritePost, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
        sqlite3_close(db_);
        return false;
    }else{
        sqlite3_close(db_);
        return true;
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}

bool PostContainer::unlike_post(Post *post, User* user) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string likes_string = post->getLikesString();

    if (likes_string.find("," + user->getUserName()) != std::string::npos) {
        int position = likes_string.find("," + user->getUserName());
        likes_string.erase(position, user->getUserName().size() + 1);
        post->setLikesString(likes_string);
    } else if (likes_string.find(user->getUserName() + ",") != std::string::npos) {
        int position = likes_string.find(user->getUserName() + ",");
        likes_string.erase(position, user->getUserName().size() + 1);
        post->setLikesString(likes_string);
    } else {
        int position = likes_string.find(user->getUserName());
        likes_string.erase(position, user->getUserName().size());
        post->setLikesString(likes_string);
    }


    std::string sqlRequest = "UPDATE posts SET likeIDs = '" + likes_string + "' where timestamp = '" + post->getTime() + "';";
    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackWritePost, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
        sqlite3_close(db_);
        return false;
    }else{
        sqlite3_close(db_);
        return true;
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}

/**
 * @brief PostContainer::send_post Used to post a post. Timestamps the post, saves to the database, and adds to the active list of posts.
 * @param content The content of the post.
 * @param user The user posting.
 * @return True if the post is sent.
 */
bool PostContainer::send_post(std::string content, User* user) {
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

    Post* post = new Post(user, content);

    std::string sqlRequest = "INSERT INTO posts (posterUsername, post, timestamp) values (\"" + user->getUserName()  + "\", \"" + content + "\", \"" + post->getTime() + "\")";
    const char *sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackWritePost, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        sqlite3_close(db_);
        return false;
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        posts_.push_back(post);
        //fprintf(stdout, "Operation done successfully\n");
    }

    refreshPost(post);

    sqlite3_close(db_);
    return true;
}

/**
 * @brief PostContainer::callbackAddPost Callback function for adding posts.
 */
int PostContainer::callbackWritePost(void *NotUsed, int argc, char **argv, char **azColName){
    return 0;
}

bool PostContainer::refreshPost(Post *post) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

        std::string sqlRequest = "SELECT * FROM posts where timestamp = \"" + post->getTime() + "\"";
        const char* sql = sqlRequest.c_str();

        code = sqlite3_exec(db_, sql, callbackRefreshPost, (void*)data, &zErrMsg);
        if(code != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            //fprintf(stderr, sql);
            sqlite3_free(zErrMsg);
            sqlite3_close(db_);
            return false;
        }else{
            //fprintf(stderr, sql);
            //fprintf(stdout, "Operation done successfully\n");
            sqlite3_close(db_);
            return true;
        }
    sqlite3_close(db_);
}

int PostContainer::callbackRefreshPost(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    std::string postID = "";
    std::string timestamp = "";
    std::string likes = "";
    for(i=0; i<argc; i++){
        switch(i)
        {
        case 0:
            postID = argv[i];
            break;
        case 3:
            timestamp = argv[i];
            break;
        case 4:
            likes = argv[i] ? argv[i] : "";
            break;
        }
    }

    for (Post* post : posts_) {
        if (post->getTime() == timestamp) {
            post->setLikesString(likes);
            post->setID(postID);
        }
    }

    return 0;
}

bool PostContainer::send_post(std::string content, User* user, std::string group_id) {
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

    Post* post = new Post(user, content);

    std::string sqlRequest = "INSERT INTO groupPosts (groupID, posterUsername, post, timestamp) values (\"" + group_id  + "\", \"" + user->getUserName()  + "\", \"" + content + "\", \"" + post->getTime() + "\")";
    const char *sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackWritePost, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        sqlite3_close(db_);
        return false;
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        posts_.push_back(post);
        //fprintf(stdout, "Operation done successfully\n");
    }

    refreshPost_group(post);

    sqlite3_close(db_);
    return true;
}

bool PostContainer::like_post_group(Post* post, User *user) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string likes_string = post->getLikesString();

    if (likes_string.size() == 0) {
        likes_string += user->getUserName();
    } else {
        likes_string += "," + user->getUserName();
    }
    post->setLikesString(likes_string);
    std::string sqlRequest = "UPDATE groupPosts SET likeIDs = '" + likes_string + "' where timestamp = '" + post->getTime() + "';";
    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackWritePost, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
        sqlite3_close(db_);
        return false;
    }else{
        sqlite3_close(db_);
        return true;
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}

bool PostContainer::unlike_post_group(Post* post, User *user) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

    std::string likes_string = post->getLikesString();

    if (likes_string.find("," + user->getUserName()) != std::string::npos) {
        int position = likes_string.find("," + user->getUserName());
        likes_string.erase(position, user->getUserName().size() + 1);
        post->setLikesString(likes_string);
    } else if (likes_string.find(user->getUserName() + ",") != std::string::npos) {
        int position = likes_string.find(user->getUserName() + ",");
        likes_string.erase(position, user->getUserName().size() + 1);
        post->setLikesString(likes_string);
    } else {
        int position = likes_string.find(user->getUserName());
        likes_string.erase(position, user->getUserName().size());
        post->setLikesString(likes_string);
    }


    std::string sqlRequest = "UPDATE groupPosts SET likeIDs = '" + likes_string + "' where timestamp = '" + post->getTime() + "';";
    const char* sql = sqlRequest.c_str();

    code = sqlite3_exec(db_, sql, callbackWritePost, (void*)data, &zErrMsg);
    if(code != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        //fprintf(stderr, sql);
        sqlite3_free(zErrMsg);
        sqlite3_close(db_);
        return false;
    }else{
        sqlite3_close(db_);
        return true;
        //fprintf(stderr, sql);
        //fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db_);
}

bool PostContainer::refreshPost_group(Post* post) {
    int code;
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    code = sqlite3_open("../../databases/database", &db_);

    if(code){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_));
        exit(0);
    }else{
        //xfprintf(stderr, "Opened database successfully\n");
    }

        std::string sqlRequest = "SELECT * FROM groupPosts where timestamp = \"" + post->getTime() + "\"";
        const char* sql = sqlRequest.c_str();

        code = sqlite3_exec(db_, sql, callbackRefreshPost, (void*)data, &zErrMsg);
        if(code != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            //fprintf(stderr, sql);
            sqlite3_free(zErrMsg);
            sqlite3_close(db_);
            return false;
        }else{
            //fprintf(stderr, sql);
            //fprintf(stdout, "Operation done successfully\n");
            sqlite3_close(db_);
            return true;
        }
    sqlite3_close(db_);
}
