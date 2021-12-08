#ifndef EOF_TYPE_H
#define EOF_TYPE_H

#include "Automaton.h"
class EOF_TYPE : public Automaton
{
public:
    EOF_TYPE() : Automaton(TokenType::EOF_TYPE) {}  // Call the base constructor

    void S0(const std::string& input) { }
};


#endif