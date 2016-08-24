#include "groupui.h"

GroupUI::GroupUI(UserContainer * user_container, User * logged_user)
{
    user_container_ = user_container;
    logged_user_ = logged_user;
    group_container_ = new GroupContainer();
    all_groupIDs_ = logged_user->getGroups(); //vector of strings
    for (int i = 0; i < all_groupIDs_.size(); i++)
    {
        int group_ID = std::stoi(all_groupIDs_[i]);
        Group * current_group = group_container_->findGroup(group_ID);
        all_groups_.push_back(current_group);
    }
}

void GroupUI::run()
{
    if (all_groupIDs_.size() > 0)
    {
        std::vector<std::string> all_group_names;
        for (int i = 0; i < all_groups_.size(); i++)
        {
            Group * group = all_groups_[i];
            std::string group_name = group->getName();
            all_group_names.push_back(group_name);
        }
        Menu * group_menu = new Menu("Groups", all_group_names);
        Group * selected_group = group_menu->run(all_groups_);

        if (selected_group != nullptr)
        {
            runGroup(selected_group);
        }
    }

    else
    {
        clear();
        printw("No groups found!\n\n{Press any key to continue}");
        getch();
    }
}

void GroupUI::runGroup(Group * group)
{
    std::string join_or_leave;
    if(logged_user_->isMember(std::to_string(group->getID())))
    {
        join_or_leave = "Leave Group";
    }

    else
    {
        join_or_leave = "Join Group";
    }

    std::vector<std::string> options { (std::string)"News Feed", (std::string)"Make Text Post", (std::string)"View Members", (std::string)"View Info", join_or_leave };
    Menu * group_menu = new Menu(group->getName().c_str(), options);
    std::string selection = group_menu->run();

    PostContainer * pc = new PostContainer(std::to_string(group->getID()));

    if (selection == "News Feed")
    {

        PostUI postui(pc, logged_user_, user_container_, true);
        postui.buildScreen();
    }

    else if (selection == "Make Text Post")
    {
        SubmitPostUI(user_container_, pc, logged_user_, group->getID());
    }

    else if (selection == "View Members")
    {
        FriendUI * fui = new FriendUI(logged_user_, logged_user_, user_container_, group_menu);
        fui->run();
    }

    else if (selection == "View Info")
    {
        clear();
        attron(A_BOLD);
        printw(group->getName().c_str());
        attroff(A_BOLD);
        printw(" @ ");
        attron(A_BOLD);
        group->setLocation("Location");
        printw(group->getLocation().c_str());
        mvprintw(0, 64, group->getDate().c_str());
        printw("\n");
        for (int i = 0; i < 79 / 2; i++)
        {
            printw(" -");
        }
        attroff(A_BOLD);
        printw("\n");
        printw(group->getDescription().c_str());
        printw("\n\n{Press any key to continue}");
        getch();
    }

    else if (selection == "Leave Group")
    {
        group_container_->removeUser(logged_user_, group->getID());
    }

    else if (selection == "Join Group")
    {
        group_container_->addUser(logged_user_, group->getID());
    }
}
