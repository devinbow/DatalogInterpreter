#ifndef String_H
#define String_H

#include "Automaton.h"
class String : public Automaton
{
public:
    String() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input);

   // void S1(const std::string& input);

    //void Serr();
};


#endif