#ifndef GROUPSWINDOW_H
#define GROUPSWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "friendswindow.h"
#include "newsfeedwindow.h"
#include "messageswindow.h"
#include "profilewindow.h"
#include "searchwindow.h"

namespace Ui {
class GroupsWindow;
}

class GroupsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GroupsWindow(QWidget *parent = 0);
    ~GroupsWindow();

private slots:
    void on_newsFeed_clicked();
    void on_logout_clicked();
    void on_friends_clicked();
    void on_messages_clicked();
    void on_myProfile_clicked();
    void on_search_clicked();

private:
    Ui::GroupsWindow *ui;
};

#endif // GROUPSWINDOW_H
