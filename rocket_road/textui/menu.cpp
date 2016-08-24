#include "menu.h"

/**
 * @brief Menu::Menu Creates a menu based on title and list of options
 * @param title The title displayed at the top of the menu
 * @param options The different options displayed in the menu
 */
Menu::Menu(std::string title, std::vector<std::string> options)
{
    min_ = 0;
    max_ = options.size() - 1;
    current_option_ = 0;
    options_ = options;
    title_ = title;
    previous_menu_ = nullptr;
}

/**
 * @brief Menu::Menu Createst a menu based on title and list of options, and allows for a menu to go back to
 * @param title The title displayed at the top of the menu
 * @param options The different options displayed in the menu
 * @param previous_menu The menu that will be navigated to upon pressing the back button
 */
Menu::Menu(std::string title, std::vector<std::string> options, Menu * previous_menu)
{
    min_ = 0;
    max_ = options.size() - 1;
    current_option_ = 0;
    options_ = options;
    title_ = title;
    previous_menu_ = previous_menu;
}

/**
 * @brief Menu::get Returns the current selected option
 * @return The current selected option
 */
int Menu::get()
{
    return current_option_;
}

User * Menu::run(std::vector<User *> all_users)
{
    std::string result = run();

    if (result.size() != 0) {
        for (int i = 0; i < all_users.size(); i++)
        {
            if (all_users[i]->getName().compare(result) == 0)
            {
                return all_users[i];
            }
        }
    } else {
        return nullptr;
    }
}

Group * Menu::run(std::vector<Group *> all_groups)
{
    std::string result = run();
    if (result.size() != 0)
    {
        for (int i = 0; i < all_groups.size(); i++)
        {
            if (all_groups[i]->getName().compare(result) == 0)
            {
                return all_groups[i];
            }
        }
    }
}

/**
 * @brief Menu::run Called to display the menu with the created information
 * @return The string associated with the selected option
 */
std::string Menu::run()
{
    while (true)
    {
        clear();
        printOptions();
        //printw(options_[current_option_].c_str());
        int ch= getch();

        //operate based on input character
        switch (ch)
        {
        case KEY_DOWN:
        case 'S':
        case 's':
            if ((current_option_ + 1) <= max_)
            {
                current_option_++;
            }

            else
            {
                current_option_ = 0;
            }

            break;
        case KEY_UP:
        case 'W':
        case 'w':
            if ((current_option_ - 1) >= min_)
            {
                current_option_--;
            }

            else
            {
                current_option_ = options_.size() - 1;
            }

            break;
        case KEY_RIGHT:
        case 10:
        case 'D':
        case 'd':
            return options_[current_option_];
            break;
        case KEY_LEFT:
        case 'A':
        case 'a':
        case 263:
            /*if (previous_menu_ != nullptr)
            {
                previous_menu_->run();           // THIS IS WHY IT DOESN'T RETURN TO THE PREVIOUS MENU
            }*/                                  // REALLY BUGGED, DON'T KNOW WHY
            return "";
            break;
        default:
            //printw(std::to_string(ch).c_str());
            break;
        }
    }

    return "Error";
}

/**
 * @brief Menu::printOptions Displays the menu's options on the screen
 */
void Menu::printOptions()
{
    int biggest = title_.size();

    for (unsigned int i = 0; i < options_.size(); i++)
    {
        if (options_[i].length() > biggest)
        {
            biggest = options_[i].length();
        }
    }
    attron(A_BOLD);
    std::string title = "";
    for (unsigned int i = 0; i < biggest; i++)
    {
        title.append("-");
    }
    int align = center(title, 1);
    mvprintw(2, align - 2, "|");
    center(title_, 2);
    mvprintw(2, align + biggest + 1, "|");
    center(title, 3);
    attroff(A_BOLD);
    for (unsigned int i = 0; i < options_.size(); i++)
    {
        attron(A_BOLD);
        mvprintw(4 + i, align - 2, "|");
        attroff(A_BOLD);
        if (i == current_option_)
        {
            attron(A_REVERSE | A_BOLD);
            mvprintw((4 + i), align, (options_[i] + (std::string)"\n").c_str());
            attroff(A_REVERSE | A_BOLD);
        }

        else
        {
            mvprintw((4 + i), align, (options_[i] + (std::string)"\n").c_str());
        }
        attron(A_BOLD);
        mvprintw(4 + i, align + biggest + 1, "|");
        attroff(A_BOLD);
    }
    attron(A_BOLD);
    center(title, 4 + options_.size());
    attroff(A_BOLD);
}

/**
 * @brief Menu::center Prints centered text at a given height
 * @param text The string to be centered
 * @param height The height the string should be centered at
 * @return The leftmost coordinate of the centered text
 */
int Menu::center(std::string text, int height)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(height,(col-(text.length()))/2,"%s",text.c_str());
    return (col-(text.length()))/2;
}
