#include "joingroupui.h"

JoinGroupUI::JoinGroupUI(User * user)
{
    current_user_ = user;
}

void JoinGroupUI::run()
{
    initscr();
    curs_set(0);
    cbreak();
    echo();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    clear();

    printw("Please enter the Group ID:\n");
    char input[80];
    getstr(input);
    std::string string_ID = input;
    int group_ID = std::stoi(string_ID);
    noecho();

    if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
    {
        GroupContainer group_container;

        if(!group_container.findGroup(group_ID))
        {
            std::vector<std::string> options { (std::string) "Yes", (std::string) "No" };
            Menu * try_again = new Menu ("Group Does Not Exist, Try Again?", options);
            std::string answer = try_again->run();

            if (answer == "Yes")
            {
                run();
            }
        }

        if(!group_container.addUser(current_user_, group_ID))
        {
            std::vector<std::string> options { (std::string) "Yes", (std::string) "No" };
            Menu * try_again = new Menu ("Unsuccessful, Try Again?", options);
            std::string answer = try_again->run();

            if (answer == "Yes")
            {
                run();
            }
        }
    }

}
