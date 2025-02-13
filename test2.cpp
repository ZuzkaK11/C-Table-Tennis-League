#include <iostream>
#include "gtest/gtest.h"

#include "Player.h"
#include "Match.h"
#include "League.h"
using namespace ::testing;

TEST(TestPlayerMethods, AddPlayers) {   //add_player(), is_player_in(), getNumberOfPlayers() - correct/wrong input
    League l;
    ASSERT_EQ("Ok",l.players.add_player("Anna Pekna"));
    ASSERT_EQ("Ok",l.players.add_player("Peter Treti"));
    ASSERT_EQ("Player already exist",l.players.add_player("Anna Pekna"));
    ASSERT_EQ("Wrong format",l.players.add_player("Karol treti7"));
    ASSERT_TRUE(l.players.is_player_in("Anna Pekna"));
    ASSERT_FALSE(l.players.is_player_in("Karol"));
    ASSERT_EQ(2,l.players.getNumberOfPlayers());
    l.deleteAll_players();
    ASSERT_EQ(0,l.players.getNumberOfPlayers());
}

TEST(TestPlayerMethods, GetPlayers) {       //get_player() - if not exist
    League l;
    ASSERT_EQ("Ok",l.players.add_player("Anna Pekna"));
    ASSERT_EQ("Ok",l.players.add_player("Peter Treti"));
    Player *p;
    p=l.players.get_player("Anna Pekna");
    ASSERT_EQ(0,p->getPoints());
    p->update(WIN);
    ASSERT_EQ(1,p->getPoints());
    ASSERT_EQ("",l.players.get_player("Maria Prva")->getName());
    ASSERT_EQ(0,l.players.get_player("Maria Prva")->getPoints());
}

TEST(TestPlayerMethods, DeletePlayers) {        //deletePlayer(), deleteAll_players()
    League l;
    std::string array[] = {"Anna Pekna","Hugo Maly","Peter Treti","Karol Prvy"};
    for (auto &name : array){
        l.players.add_player(name);
    }
    ASSERT_EQ(4,l.players.getNumberOfPlayers());
    l.deletePlayer("Anna Pekna");
    ASSERT_EQ("",l.players.get_player("Anna Pekna")->getName());
    ASSERT_EQ(3,l.players.getNumberOfPlayers());
    l.deleteAll_players();
    ASSERT_EQ(0,l.players.getNumberOfPlayers());
    ASSERT_EQ("Ok",l.players.add_player("Hugo Maly"));
    ASSERT_EQ(1,l.players.getNumberOfPlayers());
}

TEST(TestMatchMethods, AddMatches) {        //planMatch() - check conditions
    League l;
    l.players.add_player("Anna Pekna");
    l.players.add_player("Lenka Zlta");
    l.players.add_player("Peter Prvy");
    ASSERT_EQ("Ok",l.planMatch("Anna Pekna - Lenka Zlta"));
    ASSERT_EQ("Ok",l.planMatch("Anna Pekna - Peter Prvy"));
    ASSERT_EQ("Player not exist",l.planMatch("Anna Pekna - Karol 3"));
    ASSERT_EQ("Match already exist",l.planMatch("Anna Pekna - Lenka Zlta"));
    ASSERT_EQ("Match already exist",l.planMatch("Lenka Zlta - Anna Pekna"));
    ASSERT_EQ("Wrong format",l.planMatch("Anna Pekna :Lenka Zlta"));
    ASSERT_EQ(2,l.matches.getNumberOfMatches());
}

TEST(TestMatchMethods, AddMatchesResult) {  //putResults() - check conditions
    League l;
    std::string array[] = {"Anna Pekna","Lenka Zlta","Peter Prvy","Karol Treti"};
    for (auto &name : array){
        l.players.add_player(name);
    }
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.planMatch("Anna Pekna - Peter Prvy");
    l.planMatch("Karol Treti - Peter Prvy");
    ASSERT_EQ("Ok",l.putResult("Anna Pekna - Lenka Zlta 3:0"));
    ASSERT_EQ("Match already exist",l.putResult("Anna Pekna - Lenka Zlta 3:1"));
    ASSERT_EQ("Match not exist",l.putResult("Anna Pekna - Juraj Treti 3:0"));
    ASSERT_EQ("Match not exist",l.putResult("Lenka Zlta - Peter Prvy 3:0"));
    ASSERT_EQ("Wrong format",l.putResult("Karol Treti - Peter Prvy 6:8"));
    ASSERT_EQ("Wrong format",l.putResult("Karol Treti - Peter 3:2"));
}

TEST(TestMatchMethods, ReverseNames) {      //functions with reverse names
    League l;
    l.players.add_player("Anna Pekna");
    l.players.add_player("Lenka Zlta");
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.putResult("Lenka Zlta - Anna Pekna 3:0");
    ASSERT_EQ("Lenka Zlta",l.matches.get_match("Anna Pekna - Lenka Zlta")->getWinner());
    ASSERT_EQ("Lenka Zlta",l.matches.get_match("Lenka Zlta - Anna Pekna")->getWinner());
    ASSERT_EQ("3:0",l.matches.get_result("Lenka Zlta - Anna Pekna"));
    ASSERT_EQ("0:3",l.matches.get_result("Anna Pekna - Lenka Zlta"));
}

TEST(TestMatchMethods, GetPlayers) {        //get_match()
    League l;
    l.players.add_player("Anna Pekna");
    l.players.add_player("Lenka Zlta");
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.putResult("Lenka Zlta - Anna Pekna 3:0");
    Match *m;
    m=l.matches.get_match("Anna Pekna - Lenka Zlta");
    ASSERT_EQ("Lenka Zlta",m->getWinner());
    ASSERT_EQ("Anna Pekna",m->getPlayer1());
    ASSERT_EQ("Lenka Zlta",m->getPlayer2());
    ASSERT_EQ("Anna Pekna - Lenka Zlta",m->getPlayers());
    ASSERT_EQ("Lenka Zlta - Anna Pekna",m->getPlayers_reverse());
    ASSERT_EQ("",l.matches.get_match("Lenka Zlta - Hugo Maly")->getWinner());
}

TEST(TestMatchMethods, ChangeResult) {  //changeResult()
    League l;
    l.players.add_player("Anna Pekna");
    l.players.add_player("Lenka Zlta");
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.putResult("Lenka Zlta - Anna Pekna 0:3");
    Match *m;
    m = l.matches.get_match("Anna Pekna - Lenka Zlta");
    ASSERT_EQ("Anna Pekna",m->getWinner());
    ASSERT_EQ("3:0",m->getResult());
    ASSERT_FALSE(l.changeResult(m,"2:4"));
    ASSERT_TRUE(l.changeResult(m,"2:3"));
    ASSERT_EQ("Lenka Zlta",m->getWinner());
    ASSERT_EQ("2:3",m->getResult());
}


TEST(TestMatchMethods, UpdatePlayers) {     //update player's score after changing result of match
    League l;
    std::string array[]={"Anna Pekna","Lenka Zlta","Peter Prvy","Karol Treti"};
    for (auto &name : array){
        l.players.add_player(name);
    }
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.planMatch("Anna Pekna - Peter Prvy");
    l.planMatch("Karol Treti - Peter Prvy");
    l.putResult("Anna Pekna - Lenka Zlta 3:0");
    l.putResult("Anna Pekna - Peter Prvy 3:2");
    l.putResult("Karol Treti - Peter Prvy 3:2");
    ASSERT_EQ(2,l.players.get_player("Anna Pekna")->getPoints());
    ASSERT_EQ(0,l.players.get_player("Peter Prvy")->getRatio());
    Match *m, *n;
    m=l.matches.get_match("Anna Pekna - Lenka Zlta");
    l.changeResult(m,"2:3");
    n=l.matches.get_match("Karol Treti - Peter Prvy");
    l.changeResult(n,"0:3");
    ASSERT_EQ(1,l.players.get_player("Anna Pekna")->getPoints());
    ASSERT_EQ(0.5,l.players.get_player("Peter Prvy")->getRatio());
    ASSERT_EQ("Lenka Zlta",m->getWinner());
}

TEST(TestMatchMethods, ResetDeleteMatch) {  //deleteMatch(), deleteAll_matches(), resetAll_Matches()
    League l;
    std::string array[]={"Anna Pekna","Lenka Zlta","Peter Prvy","Karol Treti"};
    for (auto &name : array){
        l.players.add_player(name);
    }
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.planMatch("Anna Pekna - Peter Prvy");
    l.planMatch("Karol Treti - Peter Prvy");
    l.putResult("Anna Pekna - Lenka Zlta 3:0");
    l.putResult("Anna Pekna - Peter Prvy 3:2");
    l.putResult("Karol Treti - Peter Prvy 3:2");
    ASSERT_EQ(2,l.players.get_player("Anna Pekna")->getPoints());
    ASSERT_EQ(3,l.matches.getNumberOfMatches());
    l.deleteMatch("Anna Pekna - Lenka Zlta");
    ASSERT_EQ(1,l.players.get_player("Anna Pekna")->getPoints());
    ASSERT_EQ(2,l.matches.getNumberOfMatches());
    l.resetAll_matches();
    ASSERT_EQ(0,l.players.get_player("Anna Pekna")->getPoints());
    ASSERT_EQ(2,l.matches.getNumberOfMatches());
    l.deleteAll_matches();
    ASSERT_EQ(0,l.matches.getNumberOfMatches());
    ASSERT_FALSE(l.deleteMatch("Anna Pekna - Lenka Zlta"));
}


