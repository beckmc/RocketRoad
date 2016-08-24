#include <iostream>
#include "user.h"
#include "login.h"
#include "usercontainer.h"
#include "postcontainer.h"
#include "signup.h"
#include "date.h"
#include "post.h"

void testUserContainer(UserContainer * user_container);
void testLogin(UserContainer * user_container);
void testDate();
void testPost();

int main()
{
    Signup s;
    std::cout << s.addUser("test1@test.com", "first name", "last name", "password") << std::endl;
    UserContainer* user_container = new UserContainer();
    User * user = user_container->findUser("averyharnish@gmail.com");
    std::vector<std::string> a;
    PostContainer* pc = new PostContainer(a, user_container);
    pc->send_post("Test", user);
    //testUserContainer(user_container);
    //testLogin(user_container);
    //testDate();
    //testPost();

}

void testPost()
{
    UserContainer * user_container = new UserContainer();

    User * user = user_container->findUser("averyharnish@gmail.com");
    PostContainer *pc = new PostContainer(user->getPosters(), user_container);
    //Post * post = new Post(user_container->findUser(user->getPosters().at(0)), "This is my post.", "t");
    //std::cout << post->toString();
    //std::cout << "Welcome to rocket road" << std::endl;
    //std::cout << "Poster: " << std::endl;
    //std::cout << pc->get_posts().at(0)->getPost() << std::endl;
    //std::cout << pc->get_posts().at(1)->getPost() << std::endl;
}

void testDate()
{
    Date * date = new Date();
    std::cout << date->getDateAndTime();
}

void testUserContainer(UserContainer * user_container)
{
//    user_container->findUser("averyharnish@gmail.com")->displayInfo();
//    user_container->findUser("blauk@lafayette.edu")->displayInfo();
//    user_container->findUser("beckmc@lafayette.edu")->displayInfo();
//    user_container->findUser("pfaffmaj@lafayette.edu")->displayInfo();
}

void testLogin(UserContainer * user_container)
{
    //Login login;
    //login.run(user_container);
    /*user_1->displayInfo();
    user_1->logout();
    user_1->changePassword("password1234", "password1234", "1234password", "1234password");
    user_1->displayInfo();*/
}
