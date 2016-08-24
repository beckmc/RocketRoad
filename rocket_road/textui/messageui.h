#ifndef MESSAGEUI_H
#define MESSAGEUI_H

#include "../model/user.h"
#include "../model/usercontainer.h"
#include "../model/message.h"
#include "../model/messagecontainer.h"
#include <ncurses.h>
#include "menu.h"
#include <regex>

class MessageUI
{
public:
    MessageUI(UserContainer* userContainer, User* currentUser, User* otherUser, Menu * previous_menu);
    void run();
private:
    void loadMessages();
    void sendMessage();
    void printMessages();
    void exit();

    Menu * previous_menu_;
    MessageContainer* message_container_;
    UserContainer* user_container_;
    User* current_user_;
    User* other_user_;
    std::vector<Message*> all_messages_;
    std::vector<Message*> current_user_messages_;
    std::vector<Message*> other_user_messages_;
};

#endif // MESSAGEUI_H
