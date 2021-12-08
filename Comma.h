#ifndef Comma_H
#define Comma_H

#include "Automaton.h"
class Comma : public Automaton
{
public:
    Comma() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif