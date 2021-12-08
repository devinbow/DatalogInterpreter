#ifndef Queries_H
#define Queries_H

#include "Automaton.h"
class Queries : public Automaton
{
public:
    Queries() : Automaton(TokenType::QUERIES) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif