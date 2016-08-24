TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=                              \
        ../model/login.cpp              \
        ../model/usercontainer.cpp      \
        ../model/user.cpp               \
        ../model/group.cpp              \
        ../model/post.cpp               \
        ../model/postcontainer.cpp      \
        ../model/date.cpp               \
        ../model/signup.cpp             \
        ../model/comment.cpp            \
        ../model/commentcontainer.cpp   \
        ../model/log.cpp                \
        ../model/messagecontainer.cpp   \
        ../model/message.cpp            \
        ../model/search.cpp             \
        ../model/groupcontainer.cpp     \
        ../html/generate.cpp            \
        main.cpp                        \
        loginui.cpp                     \
        postui.cpp                      \
        menu.cpp                        \
        commentui.cpp                   \
        friendui.cpp                    \
        userui.cpp                      \
        submitpostui.cpp                \
        messageui.cpp                   \
        searchui.cpp                    \
        editui.cpp                      \
        groupui.cpp                     \
        joingroupui.cpp

HEADERS +=                              \
        ../model/login.h                \
        ../model/usercontainer.h        \
        ../model/user.h                 \
        ../model/group.h                \
        ../model/postcontainer.h        \
        ../model/post.h                 \
        ../model/date.h                 \
        ../model/signup.h               \
        ../model/comment.h              \
        ../model/commentcontainer.h     \
        ../model/log.h                  \
        ../model/messagecontainer.h     \
        ../model/message.h              \
        ../model/search.h               \
        ../model/groupcontainer.h       \
        ../html/generate.h              \
        postui.h                        \
        loginui.h                       \
        menu.h                          \
        commentui.h                     \
        friendui.h                      \
        userui.h                        \
        submitpostui.h                  \
        messageui.h                     \
        searchui.h                      \
        editui.h                        \
        groupui.h                       \
        joingroupui.h


LIBS    += -lncurses -lsqlite3
