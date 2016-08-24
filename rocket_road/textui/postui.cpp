#include "postui.h"


/**
 * @brief The comparator struct compares the time of two posts, and is used to sort the news feed from oldest to newest.
 */
struct comparator  {

    inline bool operator() (Post* p1, Post* p2)
    {
        return (p1->getTime() > p2->getTime());
    }
};

/**
 * @brief PostUI::PostUI Basic Constructor
 * @param all_posts A PostContainer holding all the posts that should appear on the current user's feed.
 */
PostUI::PostUI(PostContainer * all_posts, User* current_user, UserContainer* user_container)
{
    user_container_ = user_container;
    post_container_ = all_posts;
    current_user_ = current_user;
    post_index_ = 0;
    choice_index_ = 1;
    all_posts_ = post_container_->get_posts();
    if(all_posts_.size() > 1)
            has_next_ = true;
    else
        has_next_ = false;
    has_previous_ = false;
    is_group_ = false;
}

PostUI::PostUI(PostContainer * all_posts, User* current_user, UserContainer* user_container, bool is_group)
{
    user_container_ = user_container;
    post_container_ = all_posts;
    current_user_ = current_user;
    post_index_ = 0;
    choice_index_ = 1;
    all_posts_ = post_container_->get_posts();
    if(all_posts_.size() > 1)
            has_next_ = true;
    else
        has_next_ = false;
    has_previous_ = false;

    is_group_ = is_group;
}

/**
 * @brief PostUI::buildScreen Initializes the screen and builds the screen. No prints.
 */
void PostUI::buildScreen()
{
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    printPost();
}

//If there is an issue with scrolling, call scrollok(stdscr, FALSE);

/**
 * @brief PostUI::run Builds the screen printing all the posts and facilitates user interaction.
 */
void PostUI::printPost()
{
    clear();

    printw(" ------------------------ \n| Welcome to Rocket Road |\n ------------------------ \n\n");

    all_posts_ = post_container_->get_posts();    
    std::sort(all_posts_.begin(), all_posts_.end(), comparator());

    Date date;

    if (all_posts_.size() != 0)
    {
        attron(A_BOLD);
        printw(all_posts_.at(post_index_)->getPoster()->getName().c_str());
        attroff(A_BOLD);
        printw("\t");
        attron(A_BOLD);
        printw(date.convertDate(all_posts_.at(post_index_)->getTime()).c_str());
        attroff(A_BOLD);
        printw("\n\n");
        printw(all_posts_.at(post_index_)->getPost().c_str());
        printw("\n\nLiked by: ");
        std::vector<std::string> vect;

        std::stringstream ss(all_posts_.at(post_index_)->getLikesString().c_str());
        std::string item;
        while (std::getline(ss, item, ',')) {
            vect.push_back(item);
        }
        for (int i = 0; i < vect.size(); i++) {
            if (i > 0) {
                printw(", ");
            }
            printw(user_container_->findUser(vect.at(i))->getName().c_str());
        }
        //printw(all_posts_.at(post_index_)->getLikesString().c_str());
        //printw("\nComments: \n    ");
        //print comments.
        printw("\n\n");
        buildMenu();
    } else
    {
        printw("None of your friends have posted!\n");
        printw("Press any key to return to the Main Menu");
        refresh();
        getch();
    }
}

/**
 * @brief PostUI::buildMenu Builds the menu of options of functions for the viewer.
 */
void PostUI::buildMenu()
{
    if (choice_index_ == 1)
        attron(A_REVERSE | A_BOLD);
    if (all_posts_.at(post_index_)->likedBy(current_user_))
        printw("Unlike (L)\n");
    else
        printw("Like (L)\n");
    attroff(A_REVERSE | A_BOLD);
    if (choice_index_ == 2)
        attron(A_REVERSE | A_BOLD);
    printw("View/Make Comment(s) (C)\n");
    attroff(A_REVERSE | A_BOLD);
    if (choice_index_ == 3)
        attron(A_REVERSE | A_BOLD);
    if (has_next_)
        printw("Next Post (N)\n");
    attroff(A_REVERSE | A_BOLD);
    if (choice_index_ == 4)
        attron(A_REVERSE | A_BOLD);
    if (has_previous_)
        printw("Previous Post (P)\n");
    attroff(A_REVERSE | A_BOLD);
    if (choice_index_ == 5)
        attron(A_REVERSE | A_BOLD);
    printw("Exit (E)");
    attroff(A_REVERSE | A_BOLD);
    selectOption();
}

/**
 * @brief PostUI::selectOption Allows the user to choose what they want to do.
 * @return The index of the user's choice.
 */
int PostUI::selectOption()
{
    int select;
    while (!done_)
    {
        refresh();
        select = getch();
        switch(select)
        {
        case KEY_ENTER:
        case 10:
            if (choice_index_ == 1)  //like
            {
                if (all_posts_.at(post_index_)->likedBy(current_user_))
                    post_container_->unlike_post(all_posts_.at(post_index_), current_user_);
                else
                    post_container_->like_post(all_posts_.at(post_index_), current_user_);
                choice_index_ = 1;
            } else if (choice_index_ == 2)   //comment
            {
                choice_index_ = 1;
                if (!is_group_) {
                    CommentUI (all_posts_.at(post_index_), current_user_, user_container_);
                } else {
                  CommentUI (all_posts_.at(post_index_), current_user_, user_container_, true);
                }
            } else if (choice_index_ == 3)   //next post
            {
                post_index_++;
                choice_index_ = 1;
                postCheck();
            } else if (choice_index_ == 4)   //prev post
            {
                post_index_--;
                choice_index_ = 1;
                postCheck();
            } else                          //return to menu
            {
                done_ = true;
            }
            break;
        case 'e':
        case 'E':
            done_ = true;
            break;
        case 'l':
        case 'L':
            if (all_posts_.at(post_index_)->likedBy(current_user_))
                post_container_->unlike_post(all_posts_.at(post_index_), current_user_);
            else
                post_container_->like_post(all_posts_.at(post_index_), current_user_);
            choice_index_ = 1;
            break;
        case 'c':
        case 'C':
            choice_index_ = 1;
            if (!is_group_) {
                CommentUI (all_posts_.at(post_index_), current_user_, user_container_);
            } else {
              CommentUI (all_posts_.at(post_index_), current_user_, user_container_, true);
            }
            break;
        case 'n':
        case 'N':
            if (has_next_)
            {
                post_index_++;
                choice_index_ = 1;
                postCheck();
            }
            break;
        case 'p':
        case 'P':
            if (has_previous_)
            {
                post_index_--;
                choice_index_ = 1;
                postCheck();
            }
            break;
        case KEY_UP:
        case 'w':
        case 'W':
            if (choice_index_ != 1)
            {
                if (choice_index_ == 4 && !has_next_)
                    choice_index_ = 2;
                else if (choice_index_ == 5 && !has_previous_ && has_next_)
                    choice_index_ = 3;
                else if (choice_index_ == 5 && !has_previous_ && !has_next_)
                    choice_index_ = 2;
                else
                    choice_index_ --;
            } else
            {
                choice_index_ = 5;
            }
            break;
        case KEY_DOWN:
        case 's':
        case'S':
            if (choice_index_ != 5)
            {
                if (choice_index_ == 3 && !has_previous_)
                    choice_index_ = 5;
                else if (choice_index_ == 2 && !has_next_ && has_previous_)
                    choice_index_ = 4;
                else if (choice_index_ == 2 && !has_next_ && !has_previous_)
                    choice_index_ = 5;
                else
                    choice_index_ ++;
            } else
            {
                choice_index_ = 1;
            }
            break;
        }
        printPost();
    }
}

/**
 * @brief PostUI::postCheck Checks if there is a post before or after the current post.
 */
void PostUI::postCheck()
{
    if (post_index_ > 0)
        has_previous_ = true;
    else
        has_previous_ = false;

    if (post_index_ == (all_posts_.size() - 1))
        has_next_ = false;
    else
        has_next_ = true;
}
