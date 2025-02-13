#include "Player.h"
#include "League.h"

bool Player::putPlayer(const std::string &Name) {
    std::string first, second;
    std::string control;
    points = 0;
    matches = 0;
    for (char letter : Name) {
        if (!std::isalpha(letter) && letter != ' ' && letter != '\0') {
            return false;
        }
        if(letter == ' '){
            first = control;
            control = "";
        }
        else{
            control += letter;
        }
    }
    second = control;
    if (first.empty() || second.empty() || !std::isupper(first.front()) || !std::isupper(second.front())){
        return false;
    }
    name = Name;
    return true;
}

float Player::getRatio() const {
    if(matches == 0){
        return 0;
    }
    double ratio = static_cast<double>(points) / matches;
    return static_cast<float>(std::round(ratio * 100.0)) / 100.0;
}

void Player::update(int result) {
    if (result == LOST){        //lost
        matches++;
    }
    else if(result == WIN){      //win
        matches++;
        points++;
    }
    else if (result == RESET_LOST){     //reset lost
        if (matches-1 >= 0){
            matches--;
        }
    }
    else if (result==RESET_WIN){         //reset win
        if (matches-1 >= 0){
            matches--;
        }
        if (points-1 >= 0){
            points--;
        }
    }
}

bool Player::operator<(const Player &p) const {
    int points_second = p.getPoints();
    if (points < points_second){
        return true;
    }
    if (points == points_second){
        return getRatio() < p.getRatio();
    }
    else{
        return false;
    }
}

void Player::reset() {
    points = 0;
    matches = 0;
}
