#include "submitpostui.h"

/**
 * @brief SubmitPostUI::SubmitPostUI Basic Constructor that also runs the text interface for submitting a new post.
 * @param user_container The container of all users.
 * @param all_posts The container of all posts.
 * @param current_user The user making a post.
 */
SubmitPostUI::SubmitPostUI(UserContainer *user_container, PostContainer *all_posts, User *current_user)
{
    group_id_ = -1;
    user_container_ = user_container;
    post_container_ = all_posts;
    current_user_ = current_user;
    buildScreen();
}

SubmitPostUI::SubmitPostUI(UserContainer *user_container, PostContainer *all_posts, User *current_user, int group_id)
{
    user_container_ = user_container;
    post_container_ = all_posts;
    current_user_ = current_user;
    group_id_ = group_id;
    buildScreen();
}

/**
 * @brief SubmitPostUI::buildScreen Assigns the properties of the screen.
 */
void SubmitPostUI::buildScreen()
{
    initscr();
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    clear();
    refresh();
    printPrompt();
}

/**
 * @brief SubmitPostUI::printPrompt Prints the prompt to make a new post and submits post.
 */
void SubmitPostUI::printPrompt()
{
    clear();
    /*printw("Return to Main Menu (ESC)\n\n");
    printw(content_.c_str());
    int input;
    char character;
    bool done = false;

    input = getch();

    if (input == KEY_EXIT || input == 27)
    {
        return;
    } else if (input == 10 || input == KEY_ENTER)
    {
        done = true;
    } else if (input == 127 || input == KEY_BACKSPACE) {

        if (content_.length() > 0)
        {
            content_.erase(content_.length() - 1);
        }
        printPrompt();

    }else
    {
        character = input;
        content_ += character;
        printPrompt();
    }*/

    curs_set(1);
    printw("Return to the main menu by submitting a blank post\n\n");
    printw("What would you like to post?\n\n");

    char input[1000];
    getstr(input);
    content_ = input;


    if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
    {
        if (group_id_ == -1)
        {
            post_container_->send_post(content_, current_user_);
        }

        else
        {
            post_container_->send_post(content_, current_user_, std::to_string(group_id_));
        }
    }
    refresh();
    curs_set(0);
}
