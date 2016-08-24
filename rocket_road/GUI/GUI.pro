#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T13:31:28
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp                 \
        mainwindow.cpp              \
        ../model/login.cpp          \
        ../model/usercontainer.cpp  \
        ../model/user.cpp           \
        ../model/group.cpp          \
        ../model/post.cpp           \
        ../model/postcontainer.cpp  \
        ../model/date.cpp           \
        ../model/signup.cpp         \
        newsfeedwindow.cpp \
    menu.cpp \
    messageswindow.cpp \
    groupswindow.cpp \
    profilewindow.cpp \
    searchwindow.cpp \
    friendswindow.cpp

HEADERS  += mainwindow.h            \
        ../model/login.h            \
        ../model/usercontainer.h    \
        ../model/user.h             \
        ../model/group.h            \
        ../model/postcontainer.h    \
        ../model/post.h             \
        ../model/date.h \
        newsfeedwindow.h \
    menu.h \
    messageswindow.h \
    groupswindow.h \
    profilewindow.h \
    searchwindow.h \
    friendswindow.h

FORMS    += mainwindow.ui \
        newsfeedwindow.ui \
    menu.ui \
    friendswindow.ui \
    messageswindow.ui \
    groupswindow.ui \
    profilewindow.ui \
    searchwindow.ui

LIBS += -lsqlite3

DISTFILES +=
