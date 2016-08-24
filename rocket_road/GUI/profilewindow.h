#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "friendswindow.h"
#include "groupswindow.h"
#include "messageswindow.h"
#include "newsfeedwindow.h"
#include "searchwindow.h"

namespace Ui {
class ProfileWindow;
}

class ProfileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileWindow(QWidget *parent = 0);
    ~ProfileWindow();

private slots:
    void on_newsFeed_clicked();
    void on_logout_clicked();
    void on_friends_clicked();
    void on_groups_clicked();
    void on_messages_clicked();
    void on_search_clicked();

private:
    Ui::ProfileWindow *ui;
};

#endif // PROFILEWINDOW_H
