#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    choice_ = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete user_container_;
}

void MainWindow::setUserContainer(UserContainer *user_container)
{
    user_container_ = user_container;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString username_q = ui->usernameField->text();
    QString pass_q = ui->passwordField->text();
    std::string username = username_q.toLocal8Bit().constData();
    std::string pass = pass_q.toLocal8Bit().constData();
    Login login(user_container_);

    if (login.testUsername(username))
    {
        if (login.testPassword(user_container_->findUser(username), pass))
        {
            newsFeed = new NewsFeedWindow;
            this->close();
            newsFeed->show();
        }
    }
}

void MainWindow::on_pushButtonSignup_clicked() {
    choice_ = 1;

}

int MainWindow::getChoice()
{
    return choice_;
}
