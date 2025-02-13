#include <iostream>
#include "gtest/gtest.h"

#include "Player.h"
#include "Match.h"
#include "League.h"
using namespace ::testing;

TEST(TestPlayer, AddPlayer) {    //putPlayer(), getName()
    Player a;
    ASSERT_TRUE(a.putPlayer("Jan Kovac"));
    ASSERT_EQ("Jan Kovac",a.getName());
    Player b;
    ASSERT_FALSE(b.putPlayer("Jan kovac"));     //WRONG NAME
    ASSERT_EQ("",b.getName());
    Player c;
    ASSERT_FALSE(c.putPlayer("Jan Kova7c"));    //WRONG NAME
    Player d;
    ASSERT_FALSE(d.putPlayer("Jan"));           //WRONG NAME
}

TEST(TestPlayer, AddResult) {           //getPoints(), getMatches(), getRatio(), reset()
    Player a;
    ASSERT_TRUE(a.putPlayer("Hugo Prvy"));
    ASSERT_EQ("Hugo Prvy",a.getName());
    ASSERT_EQ(0,a.getPoints());
    ASSERT_EQ(0,a.getMatches());
    a.update(WIN);
    a.update(LOST);
    ASSERT_EQ(1,a.getPoints());
    ASSERT_EQ(2,a.getMatches());
    ASSERT_EQ(0.5,a.getRatio());
    a.reset();
    ASSERT_EQ(0,a.getPoints());
    ASSERT_EQ(0,a.getMatches());
    ASSERT_EQ(0,a.getRatio());
}

TEST(TestPlayer, Compare) {         //update()
    Player a;
    ASSERT_TRUE(a.putPlayer("Jan Kovac"));
    Player b;
    ASSERT_TRUE(b.putPlayer("Jozo Druhy"));
    Player c;
    ASSERT_FALSE(c.putPlayer("Peter maly"));    //WRONG NAME
    a.update(WIN);
    a.update(WIN);
    a.update(LOST);
    b.update(LOST);
    ASSERT_FALSE(a<b);
    ASSERT_TRUE(c<a);
}

TEST(TestMatch, PutPlayers){            //functions if wrong players
    Match m;
    ASSERT_FALSE(m.putMatch("Janko mrkva", "Jozo Prvy"));       //WRONG NAME
    ASSERT_FALSE(m.putMatch("Janko* Mrkva", "Jozo Prvy"));      //WRONG NAME
    ASSERT_FALSE(m.putMatch("Janko Mrkva", "Jozo"));            //WRONG NAME
    ASSERT_FALSE(m.putMatch("Janko Mrkva", "Janko Mrkva"));     //SAME NAME
    ASSERT_EQ(m.getPlayers(),"");
    ASSERT_EQ(m.getWinner(),"");
    ASSERT_EQ(m.getResult(),"");
    ASSERT_TRUE(m.putMatch("Janko Mrkva", "Jozo Druhy"));
    ASSERT_EQ(m.getPlayer1(),"Janko Mrkva");
    ASSERT_EQ(m.getPlayers_reverse(),"Jozo Druhy - Janko Mrkva");
}

TEST(TestMatch, Results){           //putResult(),getResult(),getResult_reverse() correct format of input
    Match m;
    m.putMatch("Janko Mrkva", "Jozo Prvy");
    ASSERT_EQ(m.getResult(),"0:0");
    m.putResult("0:3");
    ASSERT_EQ(m.getResult(),"0:3");
    ASSERT_EQ(m.getResult_reverse(),"3:0");
    Match n;
    n.putMatch("Janko Druhy", "Jozo Prvy");
    n.putResult("1:2");
    n.putResult("3:3");
    n.putResult("5:2");
    ASSERT_EQ(n.getResult(),"0:0");
    n.putResult("3:2");
    n.putResult("0:3");
    ASSERT_EQ(n.getResult(),"0:3");
}

TEST(TestMatch, GetPlayers){        //getPlayers(),getPlayers_reverse(), getWinner()
    Match m;
    m.putMatch("Janko Mrkva", "Jozo Prvy");
    ASSERT_EQ(m.getWinner(),"");
    m.putResult("0:3");
    ASSERT_EQ(m.getWinner(),"Jozo Prvy");
    m.putResult("3:2");
    ASSERT_EQ(m.getWinner(),"Janko Mrkva");
    ASSERT_EQ(m.getPlayer1(),"Janko Mrkva");
    ASSERT_EQ(m.getPlayers(), "Janko Mrkva - Jozo Prvy");
    ASSERT_EQ(m.getPlayers_reverse(), "Jozo Prvy - Janko Mrkva");
}