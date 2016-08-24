#ifndef FRIENDSWINDOW_H
#define FRIENDSWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "newsfeedwindow.h"
#include "groupswindow.h"
#include "messageswindow.h"
#include "profilewindow.h"
#include "searchwindow.h"

namespace Ui {
class FriendsWindow;
}

class FriendsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendsWindow(QWidget *parent = 0);
    ~FriendsWindow();

private slots:
    void on_newsFeed_clicked();
    void on_logout_clicked();
    void on_groups_clicked();
    void on_messages_clicked();
    void on_myProfile_clicked();
    void on_search_clicked();

private:
    Ui::FriendsWindow *ui;
};

#endif // FRIENDSWINDOW_H
