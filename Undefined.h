#ifndef UNDEFINED_H
#define UNDEFINED_H

#include "Automaton.h"
class Undefined : public Automaton
{
public:
    Undefined() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[1] == '\n') { newLines++; }
    }
};


#endif