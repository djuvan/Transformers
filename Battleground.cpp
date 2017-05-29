#include "Battleground.h"
using namespace std;

// Constructor
Battleground::Battleground() : _battleCount(0), _score(0) 
{ 
}

// Destructor
Battleground::~Battleground()
{ 
    clear();
}

// Reset/clear 
void Battleground::clear()
{ 
    // Delete Autobots
    for(int i=0; i<_autobots.size(); i++)
    {
        delete _autobots[i];
    }

    // Delete Decepticons
    for(int i=0; i<_decepticons.size(); i++)
    {
        delete _decepticons[i];
    }

    _autobots.clear();
    _decepticons.clear();
    _battleCount = 0;
    _score = 0; 
    _survivers = "";
}

// Create transformer and add it to a proper team
// 
// Params:
//      name - transformer name
//      team - A (autobots) or D (_decepticons)
//      techSpecs - array of transformer tech specs
void Battleground::add(const string& name, char team, int techSpecs[SPECCOUNT])
{
    Transformer* transformer = nullptr;
    try    
    {
        // Add transformer to appropriate team
        if(team == 'A')
            _autobots.push_back(new Transformer(name, team, techSpecs));
        else
            _decepticons.push_back(new Transformer(name, team, techSpecs));
     } 
     catch (...) 
     {
         cout << "Fatal error: Failed to add transformer to the team. End of game." << endl; 
         clear();
         exit(2);
     }
} 

// Starts battle between teams of Autobots and Decepticons
// 
// Returns:
//      Battle report string
string Battleground::battle()
{
    // Sort transformers by rank
    std::sort(_autobots.begin(), _autobots.end(), compareByRank);
    std::sort(_decepticons.begin(), _decepticons.end(), compareByRank);

    // Battle while there is matching combatant
    int i=0;
    for(; (i < _autobots.size() && i < _decepticons.size()); i++)
    {
        _battleCount++;
        int result = 0;

        // Commence battle
        try
        {
            result = _autobots[i]->battle(_decepticons[i]);
        }
        catch (OptimusVsPredakingException ex)
        {
            // Destroy all competitors, log error and rethrow exception - give 
            // application chance to gracefully handle this 'catastrophe'.
            clear();
            throw;
        }

        // Find who won the battle
        if (result == 1)
        {
            // Autobot won
            _score++;
            _autobots[i]->setBattleStatus('W');
            _decepticons[i]->setBattleStatus('L');
        }
        else if (result == 2)
        {
            // Decepticon won
            _score--;
            _decepticons[i]->setBattleStatus('W');
            _autobots[i]->setBattleStatus('L');
        }
        else
        {
            // Tie
            _decepticons[i]->setBattleStatus('T');
            _autobots[i]->setBattleStatus('T');
        }
    }

    //return battle report
    return createBattleReport(i);
} 

// Creates battle report
// 
// Returns:
//      String with following information:
//          - Number of battles
//          - The winning team
//          - Surviving members of the losing team    
//
//      Example of battle report:
//          1 battle
//          Winning team (Decepticons): Soundwave 
//          Survivors from the losing team (Autobots): Hubcap
string Battleground::createBattleReport(int lastIndex)
{
    stringstream report;
    
    // Line 1: battle count
    report  << _battleCount << " battle(s)" << endl;
    
    if(_score == 0)
    {
        // Tie
        report << "No winning team, it's a tie" << endl;
    }
    else
    {
        // Find winner and loser team
        TransformerTeam& winnerTeam = 
            (_score > 0) ? _autobots: _decepticons;
        TransformerTeam& loserTeam =
            (_score < 0) ? _autobots: _decepticons;
        
        // Line 2: winning team
        report << "Winning team (" << getWinner() << "): " 
            << createWinnerList(winnerTeam) << endl;

        // Line 3:  survivers
        _survivers = createSurviverList(loserTeam, lastIndex);
        if (_survivers.empty())
            _survivers = "None";
        report << "Survivors from the losing team ("  << getLoser() << "): " 
            << _survivers << endl;
    }

    return report.str();
}

// Create winner team list for battle report (line 2)
//
// Params: 
//      winnerTeam - winning team
string Battleground::createWinnerList(TransformerTeam& winnerTeam) const
{
    stringstream winnerList;

    for(int i=0; i < winnerTeam.size(); i++)
    {
        if(!winnerList.str().empty())
            winnerList << ", ";
        winnerList << winnerTeam[i]->getName();
        
        if(winnerTeam[i]->getBattleStatus() != ' ')
            winnerList << "(" << winnerTeam[i]->getBattleStatus() << ")";
    }

    return winnerList.str();
}

// Create survivers list for battle report (line 3)
//
// Params: 
//      loserTeam - losing team
//      lastIndex - index of last transformer when battle was stoped
string Battleground::createSurviverList(TransformerTeam& loserTeam, int lastIndex)
{
    stringstream surviverList;

    for(int i=lastIndex; i < loserTeam.size(); i++)
    {
        if(!surviverList.str().empty())
            surviverList << ", ";
        surviverList << loserTeam[i]->getName();
    }

    return surviverList.str();
}

// Get winner team name
string Battleground::getWinner() const
{ 
    if(_score == 0)
        return "";
    else
        return (_score > 0) ? "Autobots" : "Decepticons"; 
}

// Get loser team name
string Battleground::getLoser() const
{ 
    if(_score == 0)
        return "";
    else
        return (_score < 0) ? "Autobots" : "Decepticons"; 
}


