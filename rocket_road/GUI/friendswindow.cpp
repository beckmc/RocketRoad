#include "friendswindow.h"
#include "ui_friendswindow.h"

FriendsWindow::FriendsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FriendsWindow)
{
    ui->setupUi(this);
}

FriendsWindow::~FriendsWindow()
{
    delete ui;
}

void FriendsWindow::on_newsFeed_clicked() {
    NewsFeedWindow* newsFeed = new NewsFeedWindow;
    this->close();
    newsFeed->show();
}

void FriendsWindow::on_logout_clicked() {
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

void FriendsWindow::on_groups_clicked() {
    GroupsWindow* groups = new GroupsWindow;
    this->close();
    groups->show();
}

void FriendsWindow::on_messages_clicked() {
    MessagesWindow* messages = new MessagesWindow;
    this->close();
    messages->show();
}

void FriendsWindow::on_myProfile_clicked() {
    ProfileWindow* profile = new ProfileWindow;
    this->close();
    profile->show();
}

void FriendsWindow::on_search_clicked() {
    SearchWindow* search = new SearchWindow;
    this->close();
    search->show();
}
