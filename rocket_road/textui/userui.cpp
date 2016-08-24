#include "userui.h"

/**
 * @brief UserUI::UserUI Basic Constructor.
 * @param view_user The user who's profile that is being viewed.
 * @param logged_user The user who is viewing the profile.
 * @param user_container The container of all users.
 * @param previous_menu The previous menu that the text interface was on.
 */
UserUI::UserUI(User * view_user, User* logged_user, UserContainer* user_container, Menu * previous_menu)
{
    view_user_ = view_user;
    logged_user_ = logged_user;
    user_container_ = user_container;
    std::vector<std::string> username;
    username.push_back(view_user->getUserName());
    user_posts_ = new PostContainer(username, user_container);
    previous_menu_ = previous_menu;
}

/**
 * @brief UserUI::run Runs the text interface for viewing a user's profile.
 */
void UserUI::run()
{
    std::string add_or_remove;
    if (view_user_->isFriend(logged_user_))
    {
        add_or_remove = "Remove Friend";
    }

    else
    {
        add_or_remove = "Add Friend";
    }

    std::vector<std::string> options { (std::string)"View Posts",(std::string)"View Friends",(std::string)"Message"};

    if (view_user_ != logged_user_)
    {
        options.push_back(add_or_remove);
    }

    Menu * user_menu = new Menu(view_user_->getName(), options, previous_menu_);
    std::string selection = user_menu->run();  

    if (selection == "View Posts")
    {
        PostUI postui(user_posts_, logged_user_, user_container_);
        postui.buildScreen();
    }

    else if (selection == "View Friends")
    {
        FriendUI friendui(logged_user_, view_user_, user_container_, previous_menu_);
        friendui.run();
    }

    else if (selection == "Message")
    {
        MessageUI messageui(user_container_, logged_user_, view_user_, user_menu);
        messageui.run();
    }

    else if (selection == "Add Friend")
    {
        user_container_->addFriend(logged_user_, view_user_);
    }

    else if (selection == "Remove Friend")
    {
        user_container_->removeFriend(logged_user_, view_user_);
    }

    else if (selection == "View Scrapbook")
    {
        Generate * generate = new Generate(view_user_, logged_user_, user_container_);
        generate->run();
    }
}
