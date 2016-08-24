#include "loginui.h"

/**
 * @brief LoginUI::LoginUI Constructor
 * @param user_container Container of users newly refreshed the database.
 */
LoginUI::LoginUI(UserContainer * user_container)
{
    Login temp(user_container);
    login_ = temp;
    user_container_ = user_container;
}

/**
 * @brief LoginUI::run Function to setup and start the UI.
 * @return If the user correctly enters their login information return the user. Otherwize return nullptr.
 */
User* LoginUI::run() {
        //Builds Screen
        initscr();
        curs_set(0);
        cbreak();
        keypad(stdscr, TRUE);
        clear();
        std::vector<std::string> options { (std::string)"Login",(std::string)"Signup",(std::string)"Exit"};
        Menu * login_menu = new Menu((std::string)"Rocket Road", options);
        std::string answer = login_menu->run();

        if (answer == "Login") {
            return tryUsername();
        } else if (answer == "Signup") {
            return signup();
        } else if (answer == "Exit") {
            clear();
            printw("\n\nExiting!");
            refresh();
            return nullptr;
        } else {
            printw("Something went wrong in menu.cpp");
            return run();
        }
}

/**
 * @brief LoginUI::signup Runs the interface for creating a RocketRoad account.
 * @return The newly created user.
 */
User* LoginUI::signup() {
    echo();
    clear();

    char input[80];
    char inputConfirm[80];
    std::string email;
    std::string password;
    std::string firstName;
    std::string lastName;
    mvprintw(7, 20, "Sign up for Rocket Road");
    mvprintw(9, 20, "Enter Email: ");
    getstr(input);

    if (user_container_->findUser(input) != nullptr) {
        mvprintw(10, 20, "Email already taken");
        mvprintw(11, 20, "{Press any key to continue}");
        getch();
        signup();
    }

    mvprintw(10, 20, "Confirm Email: ");
    getstr(inputConfirm);
    if ((std::string)input != (std::string)inputConfirm) {
        clear();
        mvprintw(10, 20, "Emails don't match!");
        mvprintw(11, 20, "{Press any key to continue}");
        getch();
        signup();
    }
    email = (std::string)input;
    mvprintw(11, 20, "Enter Password: ");
    getstr(input);
    mvprintw(12, 20, "Confirm Password: ");
    getstr(inputConfirm);
    if ((std::string)input != (std::string)inputConfirm) {
        clear();
        mvprintw(10, 20, "Passwords don't match!");
        mvprintw(11, 20, "{Press any key to continue}");
        getch();
        signup();
    }
    password = (std::string)input;
    mvprintw(13, 20, "Enter First Name: ");
    getstr(input);
    firstName = (std::string)input;
    mvprintw(14, 20, "Enter Last Name: ");
    getstr(input);
    lastName = (std::string)input;


    Signup signup;
    if (signup.addUser(email, firstName, lastName, password)) {
        user_container_->get(email);
        return tryUsername();
    } else {
        clear();
        mvprintw(9, 20, "Email is already in use!");
    }
}

/**
 * @brief LoginUI::tryUsername Attempts to find the username in the user_container.
 * @return If the username is found and the user correctly enters their login information return the user. If its found and they fail to enter the right password then they either try again returning tryUsername(). Otherwize return nullptr.\n If the username isn't found ask the user if they want to continue. If yes return tryUsername() again. If no return nullptr.
 */
User* LoginUI::tryUsername()
{
    echo();
    clear();
    char input[80];
    mvprintw(7, 20, "Log in to Rocket Road");
    mvprintw(9, 20, "Enter Email: ");
    getstr(input);
    if (login_.testUsername(input)) {
        User * current_user = login_.loadUser(input);
        return tryPassword(current_user);
    } else {
        clear();
        char answer;
        mvprintw(9, 25, "ERROR: Username not found");
        mvprintw(10, 25, "Authentication Failed!");
        mvprintw(11, 25, "Do you want to try again? (y/n)");
        refresh();
        noecho();
        answer = getch();

        while (true)
        {
            switch(answer)
            {
            case 'y':
            case 'Y':
                return tryUsername();
                break;
            case 'n':
            case 'N':
                return run();
                break;
            default:
                answer = getch();
                break;
            }
        }

        echo();
    }
}

/**
 * @brief LoginUI::tryPassword Checks that the user knows the password to the loaded username.
 * @param current_user The user trying to login.
 * @return If the user enters the correct password return the current_user. Otherwise ask if the user wants to try again. If they do return tryUsername() if they don't return nullptr.
 */
User* LoginUI::tryPassword(User * current_user)
{
    noecho();
    mvprintw(10, 20, "Enter Password: ");
    bool done = false;
    int input;
    int index = 0;
    char character;
    std::string pass;
    //char pass[80];
    while (!done)
    {
        refresh();
        input = getch();
        if (input == 127 || input == KEY_BACKSPACE) {

            if (pass.length() > 0)
            {
                pass.erase(pass.length() - 1);
            }

            if (index > 0)
            {
                mvprintw(10, 36 + pass.length(), " ");
                index--;
            }

        } else if (input == 10 || input == KEY_ENTER)
        {

            done = true;

        } else
        {
            character = input;
            pass += character;
            mvprintw(10, 36 + index, "*");
            index ++;
        }
        //mvprintw(0, 0, "                                                 ");        //Prints the password in the upper right hand corner.
        //mvprintw(0, 0, pass.c_str());                                               //Strictly for testing convenience.
    }

    echo();
    if (login_.testPassword(current_user, pass)) {
        clear();
        mvprintw(9, 25, "Authentication Successful!");
        mvprintw(10, 25, "{Press any key to continue}");
        refresh();
        getch();
        return current_user;
    } else {
        clear();
        char answer;
        mvprintw(9, 25, "ERROR: Password Incorrect!");
        mvprintw(10, 25, "Authentication Failed!");
        mvprintw(11, 25, "Do you want to try again? (y/n)");
        refresh();
        answer = getch();
        if (answer == 'y') {
            return tryUsername();
        } else {
            clear();
            return run();
        }
    }
}
