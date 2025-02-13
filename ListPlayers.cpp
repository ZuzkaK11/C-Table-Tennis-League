#include "ListPlayers.h"
#include "League.h"

std::string ListPlayers::add_player(const std::string &name){
    if (is_player_in(name)){
        return Message[PLAYER_ALREADY_EXISTS];
    }
    Player p;
    if(p.putPlayer(name)){
        listOfPlayers.push_back(p);
        return Message[OK];
    };
    return Message[WRONG_FORMAT];
};

bool ListPlayers::is_player_in(const std::string &name) {
    for(const auto &player : listOfPlayers){
        if(player.getName() == name){
            return true;
        }
    }
    return false;
}

Player* ListPlayers::get_player(const std::string &name){
    if (is_player_in(name)) {
        for (auto &player: listOfPlayers) {
            if (player.getName() == name) {
                return &player;
            }
        }
    }
    Player *p = new Player;
    return p;

}
bool ListPlayers::update_players(const std::string &p1,const std::string &p2,const std::string &score){
    Player *P1 = get_player(p1);
    Player *P2 = get_player(p2);
    if (P1->getName().empty() || P2->getName().empty()){
        return false;
    }
    std::istringstream stream_score(score);
    int score1;
    int score2;
    char delimiter;
    if (stream_score>>score1>>delimiter>>score2){
        if(score1 >= 0 && score1 <= 3 && score2 >= 0 && score2 <= 3 && (score1 == 3 || score2 == 3) &&
           (score1 + score2 != 6) && delimiter==':' && (score1 != score2)){
            if (score1>score2){
                P1->update(WIN);
                P2->update(LOST);
            }
            else{
                P1->update(LOST);
                P2->update(WIN);
            }
            return true;
        }
    }
    return false;
}

bool ListPlayers::delete_player(const std::string &name) {
    for (auto it = listOfPlayers.begin(); it != listOfPlayers.end(); ++it) {
        if (it->getName() == name) {
            listOfPlayers.erase(it);
            return true;
        }
    }
    return false;
}

void ListPlayers::deleteAll_players() {
    listOfPlayers.clear();
}

