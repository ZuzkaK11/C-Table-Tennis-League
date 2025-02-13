#include <iostream>
#include "gtest/gtest.h"

#include "Player.h"
#include "Match.h"
#include "League.h"
using namespace ::testing;

TEST(TestReading, ReadNames) {      //readPlayers()
    League l;
    ASSERT_EQ(6,l.readPlayers("names_correct.txt"));
    l.deleteAll_players();
    ASSERT_EQ(0,l.players.getNumberOfPlayers());
    l.readPlayers("names_wrong.txt");
    ASSERT_EQ(2,l.players.getNumberOfPlayers());
}

TEST(TestReading, ReadMatches) {    //readMatches()
    League l;
    l.readPlayers("names_correct.txt");
    l.readMatches("planMatch_correct.txt");
    ASSERT_EQ(4,l.matches.getNumberOfMatches());
    l.readMatches("planMatch_wrong.txt");
    ASSERT_EQ(5,l.matches.getNumberOfMatches());
}


TEST(TestReading, Read_WriteResults) {  //writeResults()
    League l;
    l.readPlayers("names_correct.txt");
    l.readMatches("planMatch_correct.txt");
    l.readMatches("match_result.txt");
    ASSERT_EQ(4, l.matches.getNumberOfMatches());
    Match *m;
    m=l.matches.get_match("Jozef Mrkva - Karol Druhy");
    ASSERT_EQ("3:0",l.matches.get_result("Jozef Mrkva - Karol Druhy"));
    ASSERT_EQ("0:3",l.matches.get_result("Karol Druhy - Jozef Mrkva"));
    ASSERT_EQ(m->getWinner(),"Jozef Mrkva");
    l.writeResults("result1.txt");
    l.resetAll_matches();
    ASSERT_EQ(m->getWinner(),"");
    l.readMatches("result1.txt");
    ASSERT_EQ(m->getWinner(),"Jozef Mrkva");
}

TEST(TestReading, WriteTotalResults) {
    League l;
    l.readPlayers("names_correct.txt");
    l.readMatches("planMatch_correct.txt");
    l.readMatches("match_result.txt");
    l.writeTotalResults("totalresults.txt");
    l.writeResultsForEachPlayers();
    l.display_results("Jozef Mrkva");
}
