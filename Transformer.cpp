#include "Transformer.h"
using namespace std;

// Returns OptimusVsPredakingException description
const char* OptimusVsPredakingException::what() const throw()
{
    return  "Battle between Optimus Prime and Predaking brought\n"
            "destruction to all transformers in both teams.";
}

// Constructor
// 
// Params:
//      name - transformer name
//      name - team 'A' or 'D'
//      name - transformer specifications
Transformer::Transformer(std::string name, char team, int techSpecs[SPECCOUNT]) :
    _name(name),
    _team(team),
    _battleStatus(' ')
{
    for (int i = 0; i < SPECCOUNT; i++)
    {
        _techSpecs[i] = techSpecs[i];
    }
}

// Battle opposite transformer matched by rank
// 
// Params:
//      opponent - opposing transformer
// Returns:
//      1=we won, 2=opposition won, 3=tie
int Transformer::battle(const Transformer* opponent) const
{
    int res;

    // Check automatic elimination rules
    if ((res = autoEliminationByName(opponent)) > 0)
        return res;
    if ((res = autoEliminationByCourageAndStrength(opponent)) > 0)
        return res;
    if ((res = autoEliminationBySkill(opponent)) > 0)
        return res;

    // Battle winner is with one higher overallRating 
    int thisRating = getOverallRating(this);
    int opponentRating = getOverallRating(opponent);
    if(thisRating > opponentRating)
        return 1;
    else if (thisRating < opponentRating)
        return 2;
    else
        return 3;
}

// Calculate transformer overall rating
// 
// Params:
//      transformer - target transformer  
// Returns:
//      Overall rating
int Transformer::getOverallRating(const Transformer* transformer) const
{
    return transformer->getStrength() + transformer->getIntelligence() + 
            transformer->getSpeed() + transformer->getEndurance() + 
            transformer->getFirepower();
}

// Automatic elimination if opponent has name  
// Optimus Prime or Predaking, in case both fighters 
// are with super names - OptimusVsPredakingException is thrown
// 
// Params:
//      opponent - opposing transformer  
// Returns:
//      Who is automaticaly eliminated:
//      0=nobody, 1=opponent, 2=we are
int Transformer::autoEliminationByName(const Transformer* opponent) const
{
    if( getName() == "Predaking" || getName() == "Optimus Prime" )
    {
        if( opponent->getName() == "Predaking" || 
            opponent->getName() == "Optimus Prime" )
            {
                // Predaking vs Optimus Prime
                OptimusVsPredakingException ex;
                throw ex;
            }
            else
                return 1; 
    }
    else
    {
        if( opponent->getName() == "Predaking" || 
            opponent->getName() == "Optimus Prime" )
        return 2; 
    }    

    return 0;
}

// Automatic elimination if courage difference >= 4
// and strength difference >= 3
// 
// Params:
//      opponent - opposing transformer
// Returns:
//      Who is automaticaly eliminated:
//      0=nobody, 1=opponent, 2=we are
int Transformer::autoEliminationByCourageAndStrength(const Transformer* opponent) const
{
    int courageDiff = getCourage() - opponent->getCourage();
    int strengthDiff = getStrength() - opponent->getStrength();
    if(courageDiff >= 4 && strengthDiff >= 3)
        return 1;
    else if(courageDiff <= -4 && strengthDiff <= -3)
        return 2;
    else
        return 0;
}

// Automatic elimination if skill difference >= 3
//
// Params:
//      opponent - opposing transformer
// Returns:
//      Who is automaticaly eliminated:
//      0=nobody, 1=opponent, 2=we are
int Transformer::autoEliminationBySkill(const Transformer* opponent) const
{
    int skillDiff = getSkill() - opponent->getSkill();
    if(skillDiff >= 3)
        return 1;
    else if(skillDiff <= -3)
        return 2;
    else
        return 0;
}

// Custom sort (cause we are using vector of pointers in Battleground)
bool compareByRank(Transformer* a, Transformer* b)
{
    return a->getRank() > b->getRank();
}

