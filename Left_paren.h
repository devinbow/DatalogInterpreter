#ifndef Left_paren_H
#define Left_paren_H

#include "Automaton.h"
class Left_paren : public Automaton
{
public:
    Left_paren() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif