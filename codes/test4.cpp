#include <iostream>
#include "gtest/gtest.h"

#include "Player.h"
#include "Match.h"
#include "League.h"
using namespace ::testing;

TEST(TestOther, SimulateMatches) {
    League l;
    l.players.add_player("Anna Pekna");
    l.players.add_player("Lenka Zlta");
    l.players.add_player("Karol Treti");
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.putResult("Lenka Zlta - Anna Pekna 3:0");
    l.simulateNextMatches(3);
    ASSERT_EQ(1,l.matches.getNumberOfMatches());
    l.simulateNextMatches(2);
    ASSERT_EQ(3,l.matches.getNumberOfMatches());
    l.deleteAll_matches();
    l.simulateAllMatches();
    ASSERT_EQ(3,l.matches.getNumberOfMatches());
    l.display_results("");
    }

TEST(TestOther, PlayersMatches) {
    League l;
    std::string array[] = {"Anna Pekna","Lenka Zlta","Peter Prvy","Karol Treti"};
    for (auto &name : array){
        l.players.add_player(name);
    }
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.planMatch("Anna Pekna - Peter Prvy");
    l.planMatch("Karol Treti - Peter Prvy");
    l.planMatch("Karol Treti - Anna Pekna");
    l.putResult("Lenka Zlta - Anna Pekna 3:0");
    l.putResult("Anna Pekna - Peter Prvy 3:2");
    l.putResult("Karol Treti - Peter Prvy 3:2");
    std::set<std::string> m = {"Anna Pekna - Lenka Zlta 0:3","Anna Pekna - Peter Prvy 3:2","Karol Treti - Anna Pekna 0:0" };
    ASSERT_EQ(l.playerResult_set("Anna Pekna"),m);
    std::set<std::string> n = {"Anna Pekna - Lenka Zlta 0:3"};
    ASSERT_EQ(l.playerResult_set("Lenka Zlta"),n);
    ASSERT_EQ(l.playerResult_set("").size(),l.matches.getNumberOfMatches());
    l.display_results("");
}

TEST(TestOther, RemovePlayer) {
    League l;
    l.players.add_player("Anna Pekna");
    l.players.add_player("Lenka Zlta");
    l.players.add_player("Karol Treti");
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.planMatch("Anna Pekna - Karol Treti");
    l.putResult("Lenka Zlta - Anna Pekna 3:0");
    std::set<std::string> m = {"Anna Pekna - Lenka Zlta 0:3","Anna Pekna - Karol Treti 0:0"};
    ASSERT_EQ(l.playerResult_set("Anna Pekna"),m);
    ASSERT_EQ(l.players.getNumberOfPlayers(),3);
    ASSERT_EQ(l.matches.getNumberOfMatches(),2);
    l.deletePlayer("Lenka Zlta");
    ASSERT_EQ(l.players.getNumberOfPlayers(),2);
    ASSERT_EQ(l.matches.getNumberOfMatches(),1);
    std::set<std::string> n = {"Anna Pekna - Karol Treti 0:0" };
    ASSERT_EQ(l.playerResult_set("Anna Pekna"),n);
    ASSERT_EQ(l.players.get_player("Anna Pekna")->getPoints(),0);
}

TEST(TestOther, DisqPlayer) {
    League l;
    std::string array[] = {"Anna Pekna","Lenka Zlta","Peter Prvy","Karol Treti"};
    for (auto &name : array){
        l.players.add_player(name);
    }
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.planMatch("Anna Pekna - Peter Prvy");
    l.planMatch("Karol Treti - Peter Prvy");
    l.planMatch("Karol Treti - Anna Pekna");
    l.planMatch("Lenka Zlta - Peter Prvy");
    l.putResult("Lenka Zlta - Anna Pekna 3:0");
    l.putResult("Anna Pekna - Peter Prvy 3:2");
    l.putResult("Karol Treti - Anna Pekna 2:3");
    l.putResult("Lenka Zlta - Peter Prvy 3:1");
    l.display_results("");
    std::cout<<std::endl;
    std::set<std::string> m = {"Anna Pekna - Lenka Zlta 0:3","Anna Pekna - Peter Prvy 3:2","Karol Treti - Anna Pekna 2:3" };
    ASSERT_EQ(l.playerResult_set("Anna Pekna"),m);
    l.disqualifyPlayer("Anna Pekna");
    std::set<std::string> n = {"Anna Pekna - Lenka Zlta 0:3","Anna Pekna - Peter Prvy 0:3","Karol Treti - Anna Pekna 3:0" };
    ASSERT_EQ(l.playerResult_set("Anna Pekna"),n);
    ASSERT_EQ(l.players.get_player("Anna Pekna")->getPoints(),0);
    l.disqualifyPlayer("Lenka Zlta");
    std::set<std::string> o = {"Anna Pekna - Lenka Zlta 0:0","Anna Pekna - Peter Prvy 0:3","Karol Treti - Anna Pekna 3:0" };
    ASSERT_EQ(l.playerResult_set("Anna Pekna"),o);
    l.deletePlayer("Peter Prvy");
    std::set<std::string> p = {"Anna Pekna - Lenka Zlta 0:0","Karol Treti - Anna Pekna 3:0" };
    ASSERT_EQ(l.playerResult_set("Anna Pekna"),p);
    l.display_results("");

}



TEST(TestOther, ComparePLayers) {
    League l;
    std::string array[] = {"Anna Pekna","Lenka Zlta","Peter Prvy","Karol Treti"};
    for (auto &name : array){
        l.players.add_player(name);
    }
    l.planMatch("Anna Pekna - Lenka Zlta");
    l.planMatch("Anna Pekna - Peter Prvy");
    l.planMatch("Karol Treti - Peter Prvy");
    l.planMatch("Karol Treti - Anna Pekna");
    l.planMatch("Lenka Zlta - Peter Prvy");
    l.putResult("Lenka Zlta - Anna Pekna 3:0");
    l.putResult("Anna Pekna - Peter Prvy 3:2");
    l.putResult("Karol Treti - Peter Prvy 2:3");
    l.putResult("Lenka Zlta - Peter Prvy 3:1");
    l.display_ordered_players(SCORE);
    ASSERT_EQ(l.getOrderedPlayers(MATCHES)[0].getName(),"Peter Prvy");
    ASSERT_EQ(l.getOrderedPlayers(SCORE)[0].getName(),"Lenka Zlta");
    ASSERT_EQ(l.getOrderedPlayers(RATIO)[1].getName(),"Anna Pekna");
}

TEST(TestOther, OrderPLayers) {
    League l;
    l.readPlayers("names_correct.txt");
    l.readMatches("planMatch_correct.txt");
    l.readMatches("match_result.txt");
    l.display_results("");
    l.display_ordered_players(SCORE);
    Player p;
    p = l.getOrderedPlayers(SCORE)[0];
    ASSERT_EQ("Jozef Mrkva",p.getName());
}
