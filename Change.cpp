#include "League.h"

std::string League::planMatch(const std::string &match) {
    std::istringstream stream_match(match);
    std::string pl1_first, pl1_second, pl2_first, pl2_second;
    char delimiter;
    if (stream_match >> pl1_first >> pl1_second >> delimiter >> pl2_first >> pl2_second){
        std::string player1 = pl1_first + " " + pl1_second;
        std::string player2 = pl2_first + " " + pl2_second;
        if (player1 == player2 || delimiter != '-'){
            return Message[WRONG_FORMAT];
        }
        if (matches.is_match_in(match)){
            return Message[MATCH_ALREADY_EXISTS];
        }
        if (players.is_player_in(player1) && players.is_player_in(player2)){
            matches.add_match(player1, player2);
            return Message[OK];
        }
        return Message[PLAYER_DOES_NOT_EXIST];
    }
    return Message[WRONG_FORMAT];
};

std::string League::putResult(const std::string &match_result)  {
    std::istringstream stream_result(match_result);
    int score1,score2;
    std::string p1_first,p1_second,p2_first,p2_second;
    char delimiter1, delimiter2;
    if (stream_result >> p1_first >> p1_second >> delimiter1 >> p2_first >> p2_second >> score1 >> delimiter2 >> score2) {
        std::string pl1 = p1_first + " " + p1_second;
        std::string pl2 = p2_first + " " + p2_second;
        std::string match = pl1 + " - " + pl2;
        std::string score=std::to_string(score1) + ":" + std::to_string(score2);
        if (matches.is_match_in(match)) {
            Match *m = matches.get_match(match);
            if(match == m->getPlayers_reverse()){
                std::swap(score1,score2);
                std::swap(pl1,pl2);
                score = std::to_string(score1) + ":" + std::to_string(score2);
            }
            if (m->getStatus() != EXPECTED){
                return Message[MATCH_ALREADY_EXISTS];
            }
            if (m->putResult(score)){
                players.update_players(pl1,pl2,score);
                return Message[OK];
            }
            return Message[WRONG_FORMAT];
        }
        return Message[MATCH_DOES_NOT_EXIST];
    }
    return Message[WRONG_FORMAT];
}

bool League::changeResult(Match *&m, const std::string &score) {
    std::istringstream stream_score(score);
    int score1,score2;
    char delimiter1;
    if (stream_score >> score1 >> delimiter1 >> score2) {
        if ((score1 >= 0 && score1 <= 3 && score2 >= 0 && score2 <= 3 && (score1 == 3 || score2 == 3) &&
             score1 + score2 != 6) || (score1 == 0 && score2 == 0)){
            std::string pl = m->getPlayers();
            std::string p11, p12, p21, p22;
            std::istringstream stream_players(pl);
            std::string winner = m->getWinner();
            stream_players >> p11 >> p12 >> delimiter1 >> p21 >> p22;
            std::string player1 = p11 + " " + p12;
            std::string player2 = p21 + " " + p22;
            if (winner == player1){
                players.get_player(player1)->update(RESET_WIN);
                players.get_player(player2)->update(RESET_LOST);
            }
            else if(winner == player2){
                players.get_player(player2)->update(RESET_WIN);
                players.get_player(player1)->update(RESET_LOST);
            }
            m->resetResult();
            if (score != "0:0"){
                players.update_players(player1, player2, score);
            }
            if(m->putResult(score)){
                return true;
            }
        }
    }
    return false;
}

bool League::deleteMatch(const std::string &match){
    Match *m = matches.get_match(match);
    if (m->getPlayers().empty()){
        return false;
    }
    changeResult(m,"0:0");
    matches.delete_match(match);
    return true;
}

void League::deleteAll_matches() {
    for (auto  &match : matches.getMatches()){
        Match *m = matches.get_match(match.getPlayers());
        changeResult(m,"0:0");
    }
    matches.delete_all_matches();
}

void League::resetAll_matches() {
    for(auto & match:matches.getMatches()){
        Match *m = matches.get_match(match.getPlayers());
        changeResult(m,"0:0");
    }
}

bool League::deletePlayer(const std::string &name) {
    std::vector<Match> list;
    for (auto &player:players.getPlayers()) {
        if (player.getName() == name) {
            for (auto &match:matches.getMatches()){
                if(name == match.getPlayer1() ||name == match.getPlayer2()){
                    list.push_back(match);
                }
            }
            players.delete_player(name);
            for (auto &m:list){
                deleteMatch(m.getPlayers());
            }
            return true;
        }
    }
    return false;
}

void League::deleteAll_players() {
    matches.delete_all_matches();
    players.deleteAll_players();
}

void League::disqualifyPlayer(const std::string &name) {
    for (auto &match:matches.getMatches()){
        Match *m = matches.get_match(match.getPlayers());
        if(name == match.getPlayer1()){
            if (m->getStatus() == DISQ){
                changeResult(m,"0:0");
            }
            else{
                changeResult(m,"0:3");
            }
            m->setStatus(DISQ);
        }
        if(name == match.getPlayer2()){
            if (m->getStatus() == DISQ){
                changeResult(m,"0:0");
            }
            else{
                changeResult(m,"3:0");
            }
            m->setStatus(DISQ);
        }
    }
}
