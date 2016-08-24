#include "mainwindow.h"
#include "newsfeedwindow.h"
#include <QApplication>
#include "../model/usercontainer.h"
#include "newsfeedwindow.h"

void showMainWindow(UserContainer *user_container, int argc, char *argv[]);
void showNewsFeed(UserContainer *user_container, int argc, char *argv[]);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserContainer* user_container = new UserContainer();
    MainWindow w;
    w.setUserContainer(user_container);
    w.show();

    return a.exec();
}
