#include "searchui.h"

/**
 * @brief SearchUI::SearchUI Basic Constructor
 * @param user_container The container of all users.
 * @param logged_user The logged in user.
 */
SearchUI::SearchUI(UserContainer * user_container, User * logged_user)
{
    user_container_ = user_container;
    logged_user_ = logged_user;
}

/**
 * @brief SearchUI::run Builds the screen, assigns the screens properties, and runs the text interface for searching.
 */
void SearchUI::run()
{
    initscr();
    curs_set(1);
    clear();
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    clear();
    char input[100];
    printw("\nSearch: ");
    getstr(input);
    curs_set(0);
    std::string search_phrase = input;
    if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
    {
        std::vector<std::string> user_names = search(search_phrase);
        if (user_names.size() != 0)
        {
            Menu * results_menu = new Menu(std::string("Results"), user_names);
            User * selected_friend = results_menu->run(found_users_);
            UserUI * userUI = new UserUI(selected_friend, logged_user_, user_container_, results_menu);
            userUI->run();
        }
        else
        {
            printw("No results found");
            getch();
        }
    }

}

/**
 * @brief SearchUI::search Searches for users containing the specified phrase.
 * @param search_phrase The specifies phrase that is in the desired user's name.
 * @return A vector of all the names of the users that contain the specified phrase.
 */
std::vector<std::string> SearchUI::search(std::string search_phrase)
{
    Search * search = new Search(user_container_);
    found_users_ = search->findUser(search_phrase);
    std::vector<std::string> user_strings;
    if (found_users_.size() != 0)
    {
        for (int i = 0; i < found_users_.size(); i++)
        {
            user_strings.push_back(found_users_.at(i)->getName());
        }
    }

    return user_strings;
}
