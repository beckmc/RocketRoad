TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp     \
    user.cpp            \
    login.cpp           \
    group.cpp           \
    usercontainer.cpp   \
    groupcontainer.cpp \
    post.cpp \
    comment.cpp \
    postcontainer.cpp \
    date.cpp \
    signup.cpp \
    commentcontainer.cpp \
    log.cpp \
    message.cpp \
    messagecontainer.cpp \
    search.cpp

HEADERS +=              \
    user.h              \
    login.h             \
    group.h             \
    usercontainer.h     \
    groupcontainer.h \
    post.h \
    comment.h \
    postcontainer.h \
    date.h \
    signup.h \
    commentcontainer.h \
    log.h \
    message.h \
    messagecontainer.h \
    search.h

LIBS += -lsqlite3 -lncurses
