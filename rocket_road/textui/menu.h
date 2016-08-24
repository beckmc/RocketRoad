#ifndef MENU_H
#define MENU_H

#include "../model/user.h"
#include <string>
#include <vector>
#include <ncurses.h>
#include "../model/group.h"

class Menu
{
public:
    User * run(std::vector<User *> all_users);
    Group * run(std::vector<Group *> all_groups);
    Menu(std::string, std::vector<std::string> options);
    Menu(std::string title, std::vector<std::string> options, Menu * previous_menu);
    int get();
    std::string run();

private:
    int center(std::string text, int height);
    Menu * previous_menu_;
    int current_option_;
    int min_;
    int max_;
    std::string title_;
    std::vector<std::string> options_;
    void printOptions();
};

#endif // MENU_H
