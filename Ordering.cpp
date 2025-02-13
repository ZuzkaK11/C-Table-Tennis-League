#include "League.h"

bool compare_players_by_points(const Player &a, const Player &b) {
    return b < a;
}
bool compare_players_by_matches(const Player &a, const Player &b) {
    return b.getMatches() < a.getMatches();
}
bool compare_players_by_ratio(const Player &a, const Player &b) {
    return b.getRatio() < a.getRatio();
}

std::vector<Player> League::getOrderedPlayers(const int &method) {
    std::vector<Player> list = players.getPlayers();
    if (method == SCORE){
        std::sort(list.begin(), list.end(), compare_players_by_points);
    }
    if (method == RATIO){
        std::sort(list.begin(), list.end(), compare_players_by_ratio);
    }
    if (method == MATCHES){
        std::sort(list.begin(), list.end(), compare_players_by_matches);
    }
    return list;
}

void League::display_ordered_players(const int &method) {
    std::vector<Player> list=getOrderedPlayers(method);
    std::cout<<std::left << std::setw(13)<<"NAME"<<std::setw(7)
             <<"POINTS"<<std::setw(6)
             <<"RATIO"<<std::setw(6)
             <<"MATCHES"<<std::endl;
    for(auto & player : list){
        std::cout << std::left << std::setw(15) << player.getName()+":"
                  << std::setw(5) << player.getPoints() << " "
                  << std::setw(5) << player.getRatio() << " "
                  << std::setw(5) << player.getMatches() << std::endl;
    }
}


