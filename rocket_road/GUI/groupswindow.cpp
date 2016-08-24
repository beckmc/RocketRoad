#include "groupswindow.h"
#include "ui_groupswindow.h"

GroupsWindow::GroupsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GroupsWindow)
{
    ui->setupUi(this);
}

GroupsWindow::~GroupsWindow()
{
    delete ui;
}

void GroupsWindow::on_newsFeed_clicked() {
    NewsFeedWindow* newsFeed = new NewsFeedWindow;
    this->close();
    newsFeed->show();
}

void GroupsWindow::on_logout_clicked() {
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

void GroupsWindow::on_friends_clicked() {
    FriendsWindow* friends = new FriendsWindow;
    this->close();
    friends->show();
}

void GroupsWindow::on_messages_clicked() {
    MessagesWindow* messages = new MessagesWindow;
    this->close();
    messages->show();
}

void GroupsWindow::on_myProfile_clicked() {
    ProfileWindow* profile = new ProfileWindow;
    this->close();
    profile->show();
}

void GroupsWindow::on_search_clicked() {
    SearchWindow* search = new SearchWindow;
    this->close();
    search->show();
}
