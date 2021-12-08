#ifndef Period_H
#define Period_H

#include "Automaton.h"
class Period : public Automaton
{
public:
    Period() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif