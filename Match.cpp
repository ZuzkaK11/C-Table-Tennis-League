#include "Match.h"
#include "League.h"

bool Match::putMatch(const std::string &p1, const std::string &p2) {
    Player pl1,pl2;
    if(pl1.putPlayer(p1) && pl2.putPlayer(p2) && p1!=p2){
        player1 = p1;
        player2 = p2;
        result = "0:0";
        status = EXPECTED;
        return true;
    }
    return false;
}

bool Match::putResult(const std::string &score)  {
    std::istringstream stream_score(score);
    int score1;
    int score2;
    char delimiter;
    if (stream_score >> score1 >> delimiter >> score2){
        if (score1 >= 0 && score1 <= 3 && score2 >= 0 && score2 <= 3 && (score1 == 3 || score2 == 3) &&
            (score1 + score2 != 6) && delimiter == ':' && (score1!=score2)){
            result = score;
            status = DONE;
            return true;
        }
    }
    return false;
}

std::string Match::getPlayers() {
    if(player1.empty()||player2.empty()){
        return "";
    }
    return player1+" - "+player2;
}

std::string Match::getPlayers_reverse(){
    if(player1.empty()||player2.empty()){
        return "";
    }
    return player2 + " - " + player1;
}

std::string Match::getWinner() {
    std::istringstream stream_result (result);
    int score1;
    int score2;
    char delimiter;
    stream_result>>score1>>delimiter>>score2;
    if (score1>score2){
        return player1;
    }
    if (score1<score2){
        return player2;
    }
    return "";
}

std::string Match::getResult_reverse() {
    if (result.empty()){
        return "";
    }
    std::istringstream stream_result(result);
    int score1,score2;
    char delimiter;
    stream_result>>score1>>delimiter>>score2;
    return std::to_string(score2) + ":" + std::to_string(score1);
}

