#ifndef Facts_H
#define Facts_H

#include "Automaton.h"
class Facts : public Automaton
{
public:
    Facts() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif