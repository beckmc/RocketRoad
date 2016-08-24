TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    generate.cpp \
    ../model/user.cpp \
    ../model/usercontainer.cpp \
    ../model/post.cpp \
    ../model/postcontainer.cpp \
    ../model/comment.cpp \
    ../model/commentcontainer.cpp \
    ../model/log.cpp \
    ../model/date.cpp

HEADERS += \
    generate.h \
    ../model/user.h \
    ../model/usercontainer.h \
    ../model/post.h \
    ../model/postcontainer.h \
    ../model/comment.h \
    ../model/commentcontainer.h \
    ../model/log.h \
    ../model/date.h

LIBS += -lsqlite3 -lncurses
