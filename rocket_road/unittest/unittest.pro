TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += console c++11

#HEADERS += ../model/comment.h               \
#    ../model/commentcontainer.h             \
#    ../model/date.h                         \
#    ../model/group.h                        \
#    ../model/groupcontainer.h               \
#    ../model/log.h                          \
#    ../model/login.h                        \
#   ../model/message.h                      \
#    ../model/messagecontainer.h             \
#    ../model/post.h                         \
#    ../model/postcontainer.h                \
#    ../model/search.h                       \
#    ../model/signup.h                       \
#    ../model/user.h                         \
#    ../model/usercontainer.h

#SOURCES += ../model/comment.cpp             \
#    ../model/commentcontainer.cpp           \
#    ../model/date.cpp                       \
#    ../model/group.cpp                      \
#    ../model/groupcontainer.cpp             \
#    ../model/log.cpp                        \
#    ../model/login.cpp                      \
#    ../model/main.cpp                       \
#    ../model/message.cpp                    \
#    ../model/messagecontainer.cpp           \
#    ../model/post.cpp                       \
#    ../model/postcontainer.cpp              \
#    ../model/search.cpp                     \
#    ../model/signup.cpp                     \
#    ../model/user.cpp                       \
#    ../model/usercontainer.cpp

HEADERS += ../model/user.h  \
           ../model/comment.h \
           ../model/date.h  \
            ../model/post.h \
            ../model/message.h \
            ../model/login.h    \
            ../model/usercontainer.h \
            ../model/log.h  \
            ../model/group.h

SOURCES += ../model/user.cpp \
           ../model/comment.cpp \
           ../model/date.cpp  \
            ../model/post.cpp   \
            ../model/message.cpp \
            ../model/login.cpp  \
            ../model/usercontainer.cpp \
            ../model/log.cpp \
            ../model/group.cpp

SOURCES += main.cpp
INCLUDEPATH += googletest                       \
               googletest/src                   \
               googletest/src/gtest             \
               googletest/include               \
               googletest/include/gtest         \
               googletest/include/gtest/internal


LIBS +=  -L/usr/lib -Wall -Wextra -pthread -lsqlite3

SOURCES +=  "googletest/src/gtest.cc"               \
            "googletest/src/gtest-death-test.cc"    \
            "googletest/src/gtest-filepath.cc"      \
            "googletest/src/gtest-port.cc"          \
            "googletest/src/gtest-printers.cc"      \
            "googletest/src/gtest-test-part.cc"     \
            "googletest/src/gtest-typed-test.cc"
