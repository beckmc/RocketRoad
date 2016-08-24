#ifndef MESSAGESWINDOW_H
#define MESSAGESWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "friendswindow.h"
#include "groupswindow.h"
#include "newsfeedwindow.h"
#include "profilewindow.h"
#include "searchwindow.h"

namespace Ui {
class MessagesWindow;
}

class MessagesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MessagesWindow(QWidget *parent = 0);
    ~MessagesWindow();

private slots:
    void on_newsFeed_clicked();
    void on_logout_clicked();
    void on_friends_clicked();
    void on_groups_clicked();
    void on_myProfile_clicked();
    void on_search_clicked();

private:
    Ui::MessagesWindow *ui;
};

#endif // MESSAGESWINDOW_H
