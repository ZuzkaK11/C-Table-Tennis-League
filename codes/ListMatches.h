#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Match.h"
#include "Player.h"
#define PROJECT_LEAGUE_LISTMATCHES_H


class ListMatches {
private:
    std::vector<Match> listOfMatches;

public:
    std::vector<Match> getMatches(){return listOfMatches;};
    bool add_match(const std::string &player1, const std::string &player2);
    int getNumberOfMatches() const {return listOfMatches.size();};
    bool is_match_in(const std::string &match);
    Match* get_match(const std::string &match);
    std::string get_winner(const std::string &match);
    std::string get_result(const std::string &match);
    bool delete_match(const std::string &match);
    void delete_all_matches();
};


#endif //PROJECT_LEAGUE_LISTMATCHES_H
