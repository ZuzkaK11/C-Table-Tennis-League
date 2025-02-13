
#include "ListMatches.h"
#include "ListPlayers.h"
#include "League.h"

bool ListMatches::add_match(const std::string &player1, const std::string &player2) {
    if (!player1.empty() && !player2.empty()){
        Match m;
        if(m.putMatch(player1,player2)){
            listOfMatches.push_back(m);
            return true;
        }
    }
    return false;
}

bool ListMatches::is_match_in(const std::string &match) {
    for(auto & Match : listOfMatches){
        if(Match.getPlayers() == match || Match.getPlayers_reverse() == match){
            return true;
        }
    }
    return false;
}

Match* ListMatches::get_match(const std::string &match) {
    for(auto &Match : listOfMatches){
        if(Match.getPlayers() == match || Match.getPlayers_reverse() == match){
            return &Match;
        }
    }
    Match *m = new Match;
    return m;
}

std::string ListMatches::get_winner(const std::string &match) {
    Match *m = get_match(match);
    std::string winner = m->getWinner();
    return winner;
};

std::string ListMatches::get_result(const std::string &match) {
    Match *m;
    m = get_match(match);
    if (m->getPlayers() == match){
        return m->getResult();
    }
    if (m->getPlayers_reverse() == match){
        return m->getResult_reverse();
    }
    return "0:0";
}

bool ListMatches::delete_match(const std::string &match) {
    for (auto it = listOfMatches.begin(); it != listOfMatches.end(); ++it) {
        if (it->getPlayers() == match || it->getPlayers_reverse() == match) {
            listOfMatches.erase(it);
            return true;
        }
    }
    return false;
}

void ListMatches::delete_all_matches() {
    listOfMatches.clear();
}
