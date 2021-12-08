#ifndef Add_H
#define Add_H

#include "Automaton.h"
class Add : public Automaton
{
public:
    Add() : Automaton(TokenType::ADD) {}  // Call the base constructors

    void S0(const std::string& input);
};


#endif