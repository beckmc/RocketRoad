#include <iostream>
#include "loginui.h"
#include "postui.h"
#include "../model/postcontainer.h"
#include "friendui.h"
#include "submitpostui.h"
#include "searchui.h"
#include "editui.h"
#include "groupui.h"
#include "joingroupui.h"

int main()
{
    UserContainer *user_container = new UserContainer();
    User *user;
    LoginUI ui(user_container);
    user = ui.run();

    while (true)
    {
        PostContainer * allPosts = new PostContainer(user->getPosters(), user_container);

        if (user != nullptr) {
            std::vector<std::string> main_options { (std::string)"News Feed", (std::string)"Make Text Post", (std::string)"Search", (std::string) "My Groups", (std::string) "Join Group", (std::string)"My Friends", (std::string)"View Scrapbook", (std::string)"Edit Profile",(std::string)"Logout"};
            Menu * main_menu = new Menu(user->getName().c_str(), main_options);
            std::string answer = main_menu->run();
            if (answer == "Make Text Post")
            {
                user_container = new UserContainer();
                user = user_container->findUser(user->getUserName());
                SubmitPostUI makePostUI(user_container, allPosts, user);
            }
            if (answer == "News Feed")
            {
                user_container = new UserContainer();
                user = user_container->findUser(user->getUserName());
                PostUI postui(allPosts, user, user_container);
                postui.buildScreen();
            }
            else if (answer == "My Friends")
            {
                user_container = new UserContainer();
                user = user_container->findUser(user->getUserName());
                FriendUI * friendui = new FriendUI(user, user, user_container, main_menu);
                friendui->run();
            }

            else if (answer == "Search")
            {
                user_container = new UserContainer();
                user = user_container->findUser(user->getUserName());
                SearchUI * searchui = new SearchUI(user_container, user);
                searchui->run();
            }

            else if (answer == "Logout")
            {
                user = ui.run();
            }

            else if (answer == "Edit Profile")
            {
                user_container = new UserContainer();
                user = user_container->findUser(user->getUserName());
                EditUI * editui = new EditUI(user_container, user);
                editui->run();
            }

            else if (answer == "My Groups")
            {
                user_container = new UserContainer();
                user = user_container->findUser(user->getUserName());
                GroupUI * groupui = new GroupUI(user_container, user);
                groupui->run();
            }

            else if (answer == "Join Group")
            {
                user_container = new UserContainer();
                user = user_container->findUser(user->getUserName());
                JoinGroupUI * jgui = new JoinGroupUI(user);
                jgui->run();
            }

            else if (answer == "View Scrapbook")
            {
                user_container = new UserContainer();
                Generate * generate = new Generate(user, user, user_container);
                generate->run();
            }
        }
    }

    return 0;
}
