#include "commentui.h"

/**
 * @brief CommentUI::CommentUI Basic Constructor. Starts the comment textui.
 * @param post The post that is being commented on.
 * @param current_user The user that is making the comment.
 * @param user_container The container of all users.
 */
CommentUI::CommentUI(Post* post, User* current_user, UserContainer* user_container)
{

    post_ = post;
    current_user_ = current_user;
    comment_container_ = new CommentContainer(post, user_container);
    buildScreen();
}

CommentUI::CommentUI(Post* post, User* current_user, UserContainer* user_container, bool is_group)
{

    post_ = post;
    current_user_ = current_user;
    comment_container_ = new CommentContainer(post, user_container, 1);
    is_group_ = is_group;
    buildScreen();
}

/**
 * @brief CommentUI::buildScreen Sets the properties for the screen.
 */
void CommentUI::buildScreen()
{
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    clear();
    refresh();
    printPost();
}

/**
 * @brief CommentUI::printPost Prints the post that is being commented on.
 */
void CommentUI::printPost()
{
    printw("\n");
    printw(post_->getPoster()->getName().c_str());
    printw(" said:\n\n");
    printw(post_->getPost().c_str());
    printw("\n");
    for (int i = 0; i < ( 79 / 2); i++)
    {
        printw(" -");
    }
    printw("\n\n");
    printComments();
}

/**
 * @brief CommentUI::printComments Prints the other comments on the post.
 */
void CommentUI::printComments()
{
    for (int i = 0; i < comment_container_->getComments().size(); i++)
    {
        Comment * current_comment = comment_container_->getComments().at(i);
        printw(current_comment->getPoster()->getName().c_str());
        printw(" replied with:\n");
        printw(current_comment->getPost().c_str());
        printw("\n\n");
    }

    printPrompt();
}

/**
 * @brief CommentUI::printPrompt Prints the prompt for the comment, retrieves the comment,
 * and sends the comment to the container.
 */
void CommentUI::printPrompt()
{
    printw("Make a comment:\n\n");
    echo();
    refresh();

    char input[1000];
    curs_set(1);
    getstr(input);
    curs_set(0);

    std::string comment = input;
    if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
    {
        if (!is_group_)
        {
            comment_container_->send_comment(comment, current_user_, post_->getPostID());
        }

        else
        {
            comment_container_->send_comment_group(comment, current_user_, post_->getPostID());
        }
    }
    noecho();
}
