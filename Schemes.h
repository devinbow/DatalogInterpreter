#ifndef Schemes_H
#define Schemes_H

#include "Automaton.h"
class Schemes : public Automaton
{
public:
    Schemes() : Automaton(TokenType::SCHEMES) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif