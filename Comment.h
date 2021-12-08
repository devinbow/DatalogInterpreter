#ifndef Comment_H
#define Comment_H

#include "Automaton.h"
class Comment : public Automaton
{
public:
    Comment() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif