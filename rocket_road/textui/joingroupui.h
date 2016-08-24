#ifndef JOINGROUPUI_H
#define JOINGROUPUI_H

#include "../model/user.h"
#include "ncurses.h"
#include <regex>
#include "../model/groupcontainer.h"
#include "menu.h"

class JoinGroupUI
{
public:
    JoinGroupUI(User * user);
    void run();
private:
    User * current_user_;
};

#endif // JOINGROUPUI_H
