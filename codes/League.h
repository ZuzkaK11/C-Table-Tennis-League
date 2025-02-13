#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include "Match.h"
#include "Player.h"
#include "ListPlayers.h"
#include "ListMatches.h"

#ifndef PROJECT_LEAGUE_LEAGUE_H
#define PROJECT_LEAGUE_LEAGUE_H


//const std::string Compare_message[] {"Score","Ratio","Matches","Name"};
enum Compare_status {SCORE, RATIO, MATCHES, NAME};

class League {

public:
    ListPlayers players;
    ListMatches matches;
//CHANGE
    std::string planMatch(const std::string &match);
    std::string putResult(const std::string &match_result);
    bool changeResult(Match* &m,const std::string &score);
    bool deleteMatch(const std::string &match);
    void deleteAll_matches();
    void resetAll_matches();
    bool deletePlayer(const std::string &name);
    void deleteAll_players();
    void disqualifyPlayer(const std::string &name);
//READ/WRITE
    int readPlayers(const std::string &file);
    bool readMatches(const std::string &file);
    bool writeResults(const std::string &file);
    bool writeTotalResults(const std::string &file);
    bool writeResultsForEachPlayers();
//COMPARE,ORDER
    std::vector<Player> getOrderedPlayers(const int &method);
    void display_ordered_players(const int &method);
//SIMULATION
    bool simulateNextMatches(const int &number);
    void simulateAllMatches();
//OTHER
    void display_results(const std::string &name);
    std::set<std::string> playerResult_set(const std::string &name);
};


#endif //PROJECT_LEAGUE_LEAGUE_H
