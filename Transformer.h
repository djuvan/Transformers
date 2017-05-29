#ifndef __transformer_h
#define __transformer_h
#include <iostream>

#define SPECCOUNT 8

// class OptimusVsPredakingException
// Exception will be thrown if there is battle 
// between Optimus Prime and Predaking
class OptimusVsPredakingException: public std::exception
{
public:
    virtual const char* what() const throw();
};

// class Transformer
// Holds transformer properties and do  
// one on one battle with other transformer
class Transformer
{
public:
    Transformer(std::string name, char team, int techSpecs[SPECCOUNT]);
    std::string getName() const { return _name; }
    char getTeam() const { return _team; }
    const int* getTechSpecs() const { return _techSpecs; }
    int getStrength() const { return _techSpecs[0]; }
    int getIntelligence() const { return _techSpecs[1]; }
    int getSpeed() const { return _techSpecs[2]; }
    int getEndurance() const { return _techSpecs[3]; }
    int getRank() const { return _techSpecs[4]; }
    int getCourage() const { return _techSpecs[5]; }
    int getFirepower() const { return _techSpecs[6]; }
    int getSkill() const { return _techSpecs[7]; }
    int battle(const Transformer* opponent) const;
    char getBattleStatus() const { return _battleStatus; }
    void setBattleStatus(char status) { _battleStatus = status; }

private:
    std::string _name;
    char _team;
    int _techSpecs[SPECCOUNT];
    char _battleStatus; //'W', 'L' or 'T'  (win, lose or tie)

    int getOverallRating(const Transformer* transformer) const;
    int autoEliminationByName(const Transformer* opponent) const;
    int autoEliminationByCourageAndStrength(const Transformer* opponent) const;
    int autoEliminationBySkill(const Transformer* opponent) const;
};

// Custom sort function
bool compareByRank(Transformer* a, Transformer* b);

#endif //__transformer_h
