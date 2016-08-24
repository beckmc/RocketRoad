#include <gtest/gtest.h>
#include <fstream>
#include <string>
/*
#include "../model/commentcontainer.h"
#include "../model/date.h"
#include "../model/groupcontainer.h"
#include "../model/message.h"
#include "../model/messagecontainer.h"
#include "../model/postcontainer.h"
#include "../model/search.h"
#include "../model/signup.h"
#include "../model/usercontainer.h"*/
#include "../model/user.h"

#include "../model/comment.h"
#include "../model/user.h"
#include "../model/date.h"
#include "../model/post.h"
#include "../model/message.h"
#include "../model/login.h"
#include "../model/group.h"

TEST(USER, USERCONSTRUCTOR)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    ASSERT_EQ("y@3mail.com", user->getUserName());
    ASSERT_EQ("fname lname", user->getName());
    ASSERT_EQ("friend1,friend2", user->getFriendString());
    ASSERT_EQ(412, user->getID());
    ASSERT_TRUE(user->tryPassword("pword"));
}

TEST(USER, USERTRYPASSWORD)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    ASSERT_TRUE(user->tryPassword("pword"));
    ASSERT_FALSE(user->tryPassword("password123"));
}

TEST(USER, ISFRIEND)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    User* friend1 = new User("friend1", "friend1", "1", "1", "1", "1", "1", "1", 999);
    User* friend3 = new User("friend3", "friend3", "1", "1", "1", "1", "1", "1", 1001);
    ASSERT_TRUE(user->isFriend(friend1));
    ASSERT_FALSE(user->isFriend(friend3));
}

TEST(USER, ADDFRIEND)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    User* friend3 = new User("friend3", "friend3", "1", "1", "1", "1", "1", "1", 1001);
    ASSERT_FALSE(user->isFriend(friend3));
    user->addFriend(friend3);
    ASSERT_TRUE(user->isFriend(friend3));
}

TEST(USER, REMOVEFRIEND)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    User* friend1 = new User("friend1", "friend1", "1", "1", "1", "1", "1", "1", 999);
    ASSERT_TRUE(user->isFriend(friend1));
    user->removeFriend(friend1);
    ASSERT_FALSE(user->isFriend(friend1));
}

TEST(COMMENT, CONSTRUCTOR)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    Comment * comment = new Comment(user, "I like trains", "2016-04-28 12:12:12");
    ASSERT_EQ(comment->getPoster()->getName(), user->getName());
    ASSERT_EQ(comment->getPost(), "I like trains");
    ASSERT_EQ(comment->getTime(), "2016-04-28 12:12:12");
}

TEST(DATE, CONVERTDATE)
{
    Date date;
    std::string actual = date.convertDate("2016-04-28 12:12:12");
    ASSERT_EQ(actual, "12:12:12 Apr 28, 2016");
}

TEST(POST, CONSTRUCTOR)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    Post * post = new Post(user, "I like trains", "2016-04-28 12:12:12", "", "123");
    ASSERT_EQ(user->getUserName(), post->getPoster()->getUserName());
    ASSERT_EQ("I like trains", post->getPost());
    ASSERT_EQ("2016-04-28 12:12:12", post->getTime());
    ASSERT_EQ("", post->getLikesString());
    ASSERT_EQ("123", post->getPostID());
}

TEST(POST, LIKEDBY)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    User * user1 = new User("email@email.com", "email@email.com", "1", "1", "1", "1", "1", "23.jpg", 413);
    Post * post = new Post(user, "I like trains", "2016-04-28 12:12:12", "", "123");
    ASSERT_FALSE(post->likedBy(user1));
    post->setLikesString(user1->getUserName());
    ASSERT_TRUE(post->likedBy(user1));
}

TEST(POST, HASLIKES)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    User * user1 = new User("email@email.com", "email@email.com", "1", "1", "1", "1", "1", "23.jpg", 413);
    Post * post = new Post(user, "I like trains", "2016-04-28 12:12:12", "", "124");
    ASSERT_FALSE(post->hasLikes());
    post->setLikesString(user1->getName());
    ASSERT_TRUE(post->hasLikes());
}

TEST(POST, SETLIKESSTRING)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    User * user1 = new User("email@email.com", "email@email.com", "1", "1", "1", "1", "1", "23.jpg", 413);
    Post * post = new Post(user, "I like trains", "2016-04-28 12:12:12", "", "124");
    ASSERT_FALSE(post->hasLikes());
    ASSERT_TRUE(post->setLikesString(user1->getName()));
    ASSERT_TRUE(post->hasLikes());
}

TEST(MESSAGE, CONSTRUCTOR)
{
    User * user = new User("y@3mail.com", "y@3mail.com", "fname", "lname", "g1,g2", "friend1,friend2", "pword", "123.jpg", 412);
    User * user1 = new User("email@email.com", "email@email.com", "1", "1", "1", "1", "1", "23.jpg", 413);
    Message * message = new Message(user, user1, "I like trains", "2016-04-28 12:12:12");
    ASSERT_EQ(message->getToUser()->getUserName(), "y@3mail.com");
    ASSERT_EQ(message->getFromUser()->getUserName(), "email@email.com");
    ASSERT_EQ(message->getTime(), "2016-04-28 12:12:12");
    ASSERT_EQ(message->getMessage(), "I like trains");
}

TEST(LOGIN, TESTUSERNAME)
{
    Login* login = new Login();
    ASSERT_TRUE(login->testUsername("blauk@lafayette.edu"));
    ASSERT_FALSE(login->testUsername("S@($U*OIFJKDJ"));
}

TEST(LOGIN, TESTPASSWORD)
{
    Login* login = new Login();
    User* user = new User("blauk@lafayette.edu", "blauk@lafayette.edu", "Kris Blau", "1", "1", "1", "i_am_bad", "1", 1);
    ASSERT_TRUE(login->testPassword(user, "i_am_bad"));
    ASSERT_FALSE(login->testPassword(user, "Wrong Password"));
}

TEST(GROUP, CONSTRUCTOR)
{
    Group group(999, "TH_", "Description", "people", "date1", "date2");
    ASSERT_EQ(group.getName(), "TH_");
    ASSERT_EQ(group.getDescription(), "Description");
    ASSERT_EQ(group.getDate(), "date1-date2");
    ASSERT_EQ(group.getID(), 999);
    ASSERT_EQ(group.getMemberString(), "people");
}

TEST(GROUP, ADDMEMBER)
{
    Group group(999, "TH_", "Description", "", "date1", "date2");
    User* user = new User("blauk@lafayette.edu", "blauk@lafayette.edu", "Kris Blau", "1", "1", "1", "i_am_bad", "1", 1);
    ASSERT_EQ("", group.getMemberString());
    group.addMember(user);
    ASSERT_EQ("blauk@lafayette.edu", group.getMemberString());
}

TEST(GROUP, REMOVEMEMBER)
{
    Group group(999, "TH_", "Description", "", "date1", "date2");
    User* user = new User("blauk@lafayette.edu", "blauk@lafayette.edu", "Kris Blau", "1", "1", "1", "i_am_bad", "1", 1);
    group.addMember(user);
    ASSERT_EQ("blauk@lafayette.edu", group.getMemberString());
    group.removeMember(user);
    ASSERT_EQ("", group.getMemberString());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
