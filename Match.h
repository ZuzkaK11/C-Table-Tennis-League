#include <iostream>
#include <sstream>
#ifndef PROJECT_LEAGUE_MATCH_H
#define PROJECT_LEAGUE_MATCH_H

const std::string Message[] {"Done", "Expected", "Disq", "Wrong format", "Player does not exist","Match does not exist","Player already exists","Match already exists","Ok"};
enum Status {DONE, EXPECTED, DISQ, WRONG_FORMAT, PLAYER_DOES_NOT_EXIST, MATCH_DOES_NOT_EXIST, PLAYER_ALREADY_EXISTS, MATCH_ALREADY_EXISTS, OK};

class Match {
    std::string player1;
    std::string player2;
    std::string result;
    Status status;

public:
    bool putMatch(const std::string &player1, const std::string &player2);
    bool putResult(const std::string &score);
    std::string getResult(){return result;};
    std::string getResult_reverse();
    std::string getPlayer1(){return player1;}
    std::string getPlayer2(){return player2;}
    std::string getPlayers();
    std::string getPlayers_reverse();
    std::string getWinner();
    Status getStatus(){return status;};
    void setStatus(Status s){status = s;};
    void resetResult(){result = "0:0"; status = EXPECTED;}
};

#endif //PROJECT_LEAGUE_MATCH_H
