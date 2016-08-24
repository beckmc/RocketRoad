#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../model/login.h"
#include "../model/usercontainer.h"
#include "newsfeedwindow.h"

class NewsFeedWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUserContainer(UserContainer* user_container);
    int getChoice();

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonSignup_clicked();

private:
    Ui::MainWindow *ui;
    UserContainer* user_container_;
    int choice_;

    NewsFeedWindow* newsFeed;
};

#endif // MAINWINDOW_H
