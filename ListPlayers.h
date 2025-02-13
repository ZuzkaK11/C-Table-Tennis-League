#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include "Player.h"

#ifndef PROJECT_LEAGUE_LISTPLAYERS_H
#define PROJECT_LEAGUE_LISTPLAYERS_H


class ListPlayers {
private:
    std::vector<Player> listOfPlayers;

public:
    std::vector<Player> getPlayers(){return listOfPlayers;};
    std::string add_player(const std::string &name);
    int getNumberOfPlayers() const {return listOfPlayers.size();};
    bool is_player_in(const std::string &name);
    Player* get_player (const std::string &name);
    bool delete_player(const std::string &name);
    void deleteAll_players();
    bool update_players(const std::string &player1,const std::string &player2, const std::string &score);
};


#endif //PROJECT_LEAGUE_LISTPLAYERS_H
