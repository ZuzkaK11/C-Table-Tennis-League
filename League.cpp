#include "League.h"

int max_number_matches(unsigned int n) {
    int result = 0;
    n--;
    while(n!=0){
        result += n;
        n--;
    }
    return result;
}

std::set<std::string> League::playerResult_set(const std::string &name) {
    std::set<std::string> results;
    if (name.empty()){
        for (auto &match:matches.getMatches()){
            results.insert(match.getPlayers() + " " + match.getResult());
        }
    }
    else{
        for (auto &match:matches.getMatches()){
            std::string player1 = match.getPlayer1();
            std::string player2 = match.getPlayer2();
            if (name == player1 || name == player2){
                results.insert(match.getPlayers() + " " + match.getResult());
            }
        }
    }
    return results;
}

void League::display_results(const std::string &name) {
    std::set<std::string> results = playerResult_set(name);
    for (auto &match:results){
        std::cout << match << std::endl;
    }
}

bool League::simulateNextMatches(const int &number) {
    if (number+matches.getNumberOfMatches() > max_number_matches(players.getNumberOfPlayers())){
        return false;
    }
    int count = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution_player(0, players.getNumberOfPlayers()-1);
    std::uniform_int_distribution<int> distribution_score(0, 3);
    std::uniform_int_distribution<int> distribution_score2(0, 2);
    while (count<number){
        int index1 = distribution_player(gen);
        int index2 = distribution_player(gen);
        while (index1 == index2) {
            index2 = distribution_player(gen);
        }
        std::string player1 = players.getPlayers()[index1].getName();
        std::string player2 = players.getPlayers()[index2].getName();
        if(planMatch(player1 + " - " + player2) == Message[OK]){
            int score1 = distribution_score(gen);
            int score2;
            if (score1 == 3){
                score2 = distribution_score2(gen);
            }
            else{
                score2 = 3;
            }
            putResult(player1 + " - " + player2 + " " + std::to_string(score1) + ":" + std::to_string(score2));
            count++;
        }
    }
}

void League::simulateAllMatches() {
    simulateNextMatches(max_number_matches(players.getNumberOfPlayers() - matches.getNumberOfMatches()));
}