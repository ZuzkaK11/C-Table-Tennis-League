#include "League.h"

bool League::readMatches(const std::string &file) {
    std::string line;
    std::ifstream ifs(file);
    if (!ifs){
        return false;
    }
    std::string title;
    while (getline(ifs, line)) {
        std::string newLine;
        bool plan = true;
        for (char c: line) {
            switch (c) {
                case '\n':
                case '\r':
                case '\t':
                case '\b':
                case '\v':
                case '\0':
                    continue;
                default:
                    newLine += c;
                    if (c == ':'){
                        plan = false;
                    }
            }
        }
        if (plan){
            planMatch(newLine);
        }else{
            putResult(newLine);
        }
    }
    return true;
}

int League::readPlayers(const std::string &file) {
    int count = 0;
    std::string line;
    std::ifstream ifs(file);
    if (!ifs){
        return count;
    }
    while (getline(ifs, line)) {
        std::string newLine;
        for (char c: line) {
            switch (c) {
                case '\n':
                case '\r':
                case '\t':
                case '\b':
                case '\v':
                case '\0':
                    continue;
                default:
                    newLine += c;
            }
        }
        if (players.add_player(newLine) == Message[OK]){
            count++;
        }
    }
    return count;
}

bool League::writeResults(const std::string &file) {
    if (matches.getNumberOfMatches() == 0){
        return false;
    }
    std::ofstream outFile(file);
    if (!outFile) {
        return false;
    }
    for(auto & Match : matches.getMatches()){
        if (Match.getResult() == "0:0"){
            outFile << Match.getPlayers() << "\r" << "\n";
        }
        else{
            outFile << Match.getPlayers() << " " << Match.getResult() << "\r" << "\n";
        }
    }
    return true;
}

bool League::writeTotalResults(const std::string &file) {
    std::ofstream outFile(file);
    if (!outFile) {
        return false;
    }
    std::vector<Player> list= getOrderedPlayers(SCORE);
    outFile << std::left << std::setw(13) << "NAME" << std::setw(7)
            << "POINTS" << std::setw(6)
            << "RATIO" << std::setw(6)
            << "MATCHES" << "\r" << "\n";
    for (auto &p:list){
            outFile << std::left << std::setw(15) << p.getName()+":"
                    << std::setw(5) << p.getPoints() << " "
                    << std::setw(5) << p.getRatio() << " "
                    << std::setw(5) << p.getMatches() <<"\r"<<"\n";
        }
    for(auto & Match : matches.getMatches()){
        if (Match.getResult() == "0:0"){
            outFile << Match.getPlayers() << "\r" << "\n";
        }
        else{
            outFile << Match.getPlayers() << " " << Match.getResult() << "\r" << "\n";
        }
    }
    return true;

}

bool League::writeResultsForEachPlayers() {
    std::vector<Player> list = getOrderedPlayers(SCORE);
    std::ofstream outFile("all.txt");
    if (!outFile) {
        return false;
    }
    for(auto &p:list){
        outFile << std::left << std::setw(13) << "NAME" << std::setw(7)
                << "POINTS" <<std::setw(6)
                << "RATIO" <<std::setw(6)
                << "MATCHES" <<"\r"<<"\n";
        outFile << std::left << std::setw(15) << p.getName()+":"
                << std::setw(5) << p.getPoints() << " "
                << std::setw(5) << p.getRatio() << " "
                << std::setw(5) << p.getMatches() << "\r" << "\n";
        std::set<std::string> match = playerResult_set(p.getName());
        for(auto &m:match){
            outFile << m << "\r" << "\n";
        }
        outFile << std::endl;
    }
    return true;
}