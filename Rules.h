#ifndef Rules_H
#define Rules_H

#include "Automaton.h"
class Rules : public Automaton
{
public:
    Rules() : Automaton(TokenType::RULES) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif