#ifndef NEWSFEEDWINDOW_H
#define NEWSFEEDWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "mainwindow.h"
#include "friendswindow.h"
#include "groupswindow.h"
#include "messageswindow.h"
#include "profilewindow.h"
#include "searchwindow.h"
#include "../model/post.h"
#include "../model/user.h"
#include "../model/postcontainer.h"
#include "../model/usercontainer.h"

namespace Ui {
class NewsFeedWindow;
}

class NewsFeedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewsFeedWindow(QWidget *parent = 0);
    ~NewsFeedWindow();
    void setUser(User* user);
    void displayPosts();

private slots:
    void on_logout_clicked();
    void on_friends_clicked();
    void on_groups_clicked();
    void on_messages_clicked();
    void on_myProfile_clicked();
    void on_search_clicked();

private:
    Ui::NewsFeedWindow *ui;
    User* current_user_;
    PostContainer* post_container_;
    UserContainer* user_container_;
    std::vector<Post*> all_posts_;
};

#endif // NEWSFEEDWINDOW_H
