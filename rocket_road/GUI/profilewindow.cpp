#include "profilewindow.h"
#include "ui_profilewindow.h"

ProfileWindow::ProfileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);
}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}

void ProfileWindow::on_newsFeed_clicked() {
    NewsFeedWindow* newsFeed = new NewsFeedWindow;
    this->close();
    newsFeed->show();
}

void ProfileWindow::on_logout_clicked() {
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

void ProfileWindow::on_friends_clicked() {
    FriendsWindow* friends = new FriendsWindow;
    this->close();
    friends->show();
}

void ProfileWindow::on_groups_clicked() {
    GroupsWindow* groups = new GroupsWindow;
    this->close();
    groups->show();
}

void ProfileWindow::on_messages_clicked() {
    MessagesWindow* messages = new MessagesWindow;
    this->close();
    messages->show();
}

void ProfileWindow::on_search_clicked() {
    SearchWindow* search = new SearchWindow;
    this->close();
    search->show();
}
