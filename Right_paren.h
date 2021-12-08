#ifndef Right_paren_H
#define Right_paren_H

#include "Automaton.h"
class Right_paren : public Automaton
{
public:
    Right_paren() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif