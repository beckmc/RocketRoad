#include "friendui.h"

/**
 * @brief The comparator struct Compares which user's name comes first in the alphabet.
 */
struct comparator
{
    inline bool operator() (User* user1, User* user2)
    {
        return (user1->getName() < user2->getName());
    }
};

/**
 * @brief FriendUI::FriendUI Basic constructor
 * @param logged_user The user who is currently logged in.
 * @param current_user The user who's friends are being loaded.
 * @param all_users The container of all users.
 * @param previous_menu The previous menu that the text interface was on.
 */
FriendUI::FriendUI(User * logged_user, User * current_user, UserContainer * all_users, Menu * previous_menu)
{
    logged_user_ = logged_user;
    all_users_ = all_users;
    current_user_ = current_user;
    std::vector<std::string> all_friendIDs = current_user->getFriends();
    for (int i = 0; i < all_friendIDs.size(); i++)
    {
        all_friends_.push_back(all_users->findUser(all_friendIDs[i]));
    }

    std::sort(all_friends_.begin(), all_friends_.end(), comparator());
    previous_menu_ = previous_menu;
}

/**
 * @brief FriendUI::run Runs the text interface for viewing ones friends list.
 */
void FriendUI::run()
{
    if (all_friends_.size() > 0)
    {
        std::vector<std::string> all_friend_names;
        for (int i = 0; i < all_friends_.size(); i ++)
        {
            all_friend_names.push_back(all_friends_[i]->getName());
        }

        Menu * friend_menu = new Menu((std::string)"Friends", all_friend_names, previous_menu_);
        User * selected_friend = friend_menu->run(all_friends_);
        if (selected_friend != nullptr) {
            UserUI * userUI = new UserUI(selected_friend, logged_user_, all_users_, friend_menu);
            userUI->run();
        }
    }

    else
    {
        clear();
        printw("No friends found!\n\n{Press any key to continue}");
        getch();
    }
}

// To handle each individual friend, we need to compare the selected_friend variable
// to find an actual User object, and then display the information regarding that friend
