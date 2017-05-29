#ifndef __battleground_h
#define __battleground_h

#include <sstream>
#include <queue>
#include <exception>
#include "Transformer.h"

// Collection of transformers sorted by rank
typedef std::vector<Transformer*> TransformerTeam;

// class Battleground
// Game where autobots and decepticons battle
class Battleground
{
public:
    Battleground();
    ~Battleground();
    void add(const std::string& name, char team, int techSpecs[SPECCOUNT]);
    std::string battle();
    int getBattleCount() const { return _battleCount; }
    std::string getSurvivers() const { return _survivers; }
    std::string getWinner() const;
    void clear();

private:
    TransformerTeam _autobots;
    TransformerTeam _decepticons;
    int _battleCount;
    int _score; 
    std::string _survivers;

    std::string createWinnerList(TransformerTeam& winnerTeam) const;
    std::string createSurviverList(TransformerTeam& loserTeam, int lastIndex);
    std::string createBattleReport(int lastIndex);
    std::string getLoser() const;
};

#endif //__battleground_h