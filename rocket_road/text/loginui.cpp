#include "loginui.h"

LoginUI::LoginUI(UserContainer* user_container)
{
    UserContainer * user_container = new UserContainer();
    user_container->findUser("averyharnish@gmail.com")->displayInfo();
    user_container->findUser("blauk@lafayette.edu")->displayInfo();
    user_container->findUser("beckmc@lafayette.edu")->displayInfo();
    user_container->findUser("pfaffmaj@lafayette.edu")->displayInfo();
}
