#include "editui.h"

/**
 * @brief EditUI::EditUI Basic constructor.
 * @param user_container The container of all users.
 * @param logged_user The user that is editing their profile.
 */
EditUI::EditUI(UserContainer * user_container, User * logged_user)
{
    user_container_ = user_container;
    logged_user_ = logged_user;
}

/**
 * @brief EditUI::run Runs the text interface for editing a users profile.
 */
void EditUI::run()
{
    std::vector<std::string> options { (std::string)"First Name", (std::string)"Last Name", (std::string)"Password" };
    Menu * edit_menu = new Menu("Edit Profile", options);
    std::string selection = edit_menu->run();

    if (selection == "First Name")
    {
        clear();
        printw("Enter new first name: ");
        curs_set(1);
        char input[80];
        if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
        {
            getstr(input);
            std::string first_name = input;
            user_container_->editFirstName(logged_user_, first_name);

        }
        curs_set(0);

    }

    else if (selection == "Last Name")
    {
        clear();
        printw("Enter new last name: ");
        curs_set(1);
        char input[80];
        if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
        {
            getstr(input);
            std::string last_name = input;
            user_container_->editLastName(logged_user_, last_name);
        }

        curs_set(0);
    }

    else if (selection == "Password")
    {
        echo();

        bool pass_correct = false;

        while (!pass_correct)
        {
            echo();
            clear();
            printw("Enter old password: ");
            curs_set(1);
            char input[80];
            getstr(input);
            if (std::regex_replace(input, std::regex("^ +| +$|( ) +"), "$1") != "")
            {
                std::string old_password = input;

                if(logged_user_->tryPassword(old_password))
                {
                    echo();
                    pass_correct = true;
                    clear();
                    bool confirm_correct = false;
                    while(!confirm_correct)
                    {
                        clear();
                        printw("Enter desired password: ");
                        char input1[80];
                        getstr(input1);
                        if (std::regex_replace(input1, std::regex("^ +| +$|( ) +"), "$1") != "")
                        {
                            std::string new_password = input1;
                            printw("\nConfirm new password: ");
                            char input2[80];
                            if (std::regex_replace(input2, std::regex("^ +| +$|( ) +"), "$1") != "")
                            {
                                getstr(input2);
                                std::string confirm_password = input2;
                                if (new_password == confirm_password)
                                {
                                    user_container_->editPassword(logged_user_, confirm_password);
                                    confirm_correct = true;
                                }

                                else
                                {
                                    curs_set(0);
                                    printw("\nPasswords do not match\n{Press any key to continue}");
                                    getch();
                                }
                            }

                        }

                    }
                }

            }

            else
            {
                curs_set(0);
                printw("\nIncorrect password\n{Press any key to continue}");
                getch();
            }

            noecho();

            curs_set(0);
        }
    }
}
