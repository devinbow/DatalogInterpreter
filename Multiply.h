#ifndef Multiply_H
#define Multiply_H

#include "Automaton.h"
class Multiply : public Automaton
{
public:
    Multiply() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif