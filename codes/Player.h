#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

#ifndef PROJECT_LEAGUE_PLAYER_H
#define PROJECT_LEAGUE_PLAYER_H

//const std::string Result_message[] {"Win","Lost","Reset_win","Reset_lost"};
enum Result_status {WIN, LOST, RESET_WIN, RESET_LOST};

class Player {
    std::string name;
    int points;
    int matches;

public:
    bool putPlayer(const std::string &Name);
    int getPoints() const {return points;};
    int getMatches() const {return matches;};
    std::string getName() const {return name;};
    float getRatio() const;
    void update(int result);
    bool operator < (const Player &p) const;
    void reset();
};


#endif //PROJECT_LEAGUE_PLAYER_H
