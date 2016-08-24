#include "messageui.h"

/**
 * @brief The comparator struct Compares which message was sent first.
 */
struct comparator {

    inline bool operator() (Message* m1, Message* m2) {
        return (m1->getTime() < m2->getTime());
    }

};

/**
 * @brief MessageUI::MessageUI Basic Constructor
 * @param userContainer Container of all users.
 * @param currentUser The user that is opening a conversation.
 * @param otherUser The other user in the conversation.
 * @param previous_menu The previous menu the text interface was on.
 */
MessageUI::MessageUI(UserContainer *userContainer, User *currentUser, User *otherUser, Menu * previous_menu)
{
    user_container_ = userContainer;
    current_user_ = currentUser;
    other_user_ = otherUser;
    previous_menu_ = previous_menu;
}

/**
 * @brief MessageUI::loadMessages Loads the previous messages between the two users.
 */
void MessageUI::loadMessages() {
    message_container_ = new MessageContainer(user_container_, current_user_, other_user_);
    all_messages_.clear();
    all_messages_ = message_container_->get_messages();
    std::sort(all_messages_.begin(), all_messages_.end(), comparator());
}

/**
 * @brief MessageUI::sendMessage Sends a message from the currentUser to the otherUser.
 */
void MessageUI::sendMessage()
{
    printw("\nMessage: ");
    echo();
    refresh();
    curs_set(1);
    char input[1000];
    getstr(input);
    std::string message = input;

    if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
    {
        message_container_->send_message(other_user_, current_user_, message);
    }

    run();
}

/**
 * @brief MessageUI::run Builds the screen, assigns the screen's properties, and runs the text interface for messaging.
 */
void MessageUI::run()
{
    loadMessages();
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    clear();
    printMessages();
    int ch = getch();

    switch (ch)
    {
    case 'n':
    case 'N':
        sendMessage();
        break;
    case 'r':
    case 'R':
        loadMessages();
        run();
        break;
    case 'x':
    case 'X':
        exit();
        break;
    default:
        run();
        break;
    }
}

/**
 * @brief MessageUI::exit Exits the text interface for messaging.
 */
void MessageUI::exit()
{
    previous_menu_->run();
}

/**
 * @brief MessageUI::printMessages Prints the messages between the two users.
 */
void MessageUI::printMessages()
{
    Date date;

    for (int i = 0; i < all_messages_.size(); i++)
    {
        Message * current_message = all_messages_[i];
        attron(A_BOLD);
        printw(current_message->getFromUser()->getName().c_str());
        printw("\t\t\t\t\t\t  ");
        printw(date.convertDate(current_message->getTime()).c_str());
        printw("\n\n");
        attroff(A_BOLD);
        printw(current_message->getMessage().c_str());
        printw("\n-------------------------------------------------------------------------------\n");
    }

    printw("         ");
    attron(A_BOLD | A_REVERSE);
    printw("  N - New Message\t\tR - Refresh\t\tX - Exit  ");
    attroff(A_BOLD | A_REVERSE);
    refresh();
}
