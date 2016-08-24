TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    loginui.cpp

LIBS += -lncurses

HEADERS += \
    loginui.h
