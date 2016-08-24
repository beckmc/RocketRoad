#include "messageswindow.h"
#include "ui_messageswindow.h"

MessagesWindow::MessagesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MessagesWindow)
{
    ui->setupUi(this);
}

MessagesWindow::~MessagesWindow()
{
    delete ui;
}

void MessagesWindow::on_newsFeed_clicked() {
    NewsFeedWindow* newsFeed = new NewsFeedWindow;
    this->close();
    newsFeed->show();
}

void MessagesWindow::on_logout_clicked() {
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}

void MessagesWindow::on_friends_clicked() {
    FriendsWindow* friends = new FriendsWindow;
    this->close();
    friends->show();
}

void MessagesWindow::on_groups_clicked() {
    GroupsWindow* groups = new GroupsWindow;
    this->close();
    groups->show();
}

void MessagesWindow::on_myProfile_clicked() {
    ProfileWindow* profile = new ProfileWindow;
    this->close();
    profile->show();
}

void MessagesWindow::on_search_clicked() {
    SearchWindow* search = new SearchWindow;
    this->close();
    search->show();
}
