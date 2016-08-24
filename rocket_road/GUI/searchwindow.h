#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "friendswindow.h"
#include "groupswindow.h"
#include "messageswindow.h"
#include "profilewindow.h"
#include "newsfeedwindow.h"

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

private slots:
    void on_newsFeed_clicked();
    void on_logout_clicked();
    void on_friends_clicked();
    void on_groups_clicked();
    void on_messages_clicked();
    void on_myProfile_clicked();

private:
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
