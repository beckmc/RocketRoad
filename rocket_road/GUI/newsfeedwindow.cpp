#include "newsfeedwindow.h"
#include "ui_newsfeedwindow.h"

NewsFeedWindow::NewsFeedWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewsFeedWindow)
{
    ui->setupUi(this);
}

NewsFeedWindow::~NewsFeedWindow()
{
    delete ui;
}

void NewsFeedWindow::setUser(User* user)
{
    current_user_ = user;
}

void NewsFeedWindow::displayPosts()
{
    all_posts_ = post_container_->get_posts();
    all_posts_.at(0)->getPoster()->getName();
}

void NewsFeedWindow::on_logout_clicked() {
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

void NewsFeedWindow::on_friends_clicked() {
    FriendsWindow* friends = new FriendsWindow;
    this->close();
    friends->show();
}

void NewsFeedWindow::on_groups_clicked() {
    GroupsWindow* groups = new GroupsWindow;
    this->close();
    groups->show();
}

void NewsFeedWindow::on_messages_clicked() {
    MessagesWindow* messages = new MessagesWindow;
    this->close();
    messages->show();
}

void NewsFeedWindow::on_myProfile_clicked() {
    ProfileWindow* profile = new ProfileWindow;
    this->close();
    profile->show();
}

void NewsFeedWindow::on_search_clicked() {
    SearchWindow* search = new SearchWindow;
    this->close();
    search->show();
}
