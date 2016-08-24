#include "searchwindow.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::on_newsFeed_clicked() {
    NewsFeedWindow* newsFeed = new NewsFeedWindow;
    this->close();
    newsFeed->show();
}

void SearchWindow::on_logout_clicked() {
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

void SearchWindow::on_friends_clicked() {
    FriendsWindow* friends = new FriendsWindow;
    this->close();
    friends->show();
}

void SearchWindow::on_groups_clicked() {
    GroupsWindow* groups = new GroupsWindow;
    this->close();
    groups->show();
}

void SearchWindow::on_messages_clicked() {
    MessagesWindow* messages = new MessagesWindow;
    this->close();
    messages->show();
}

void SearchWindow::on_myProfile_clicked() {
    ProfileWindow* profile = new ProfileWindow;
    this->close();
    profile->show();
}
