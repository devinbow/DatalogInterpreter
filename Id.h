#ifndef Id_H
#define Id_H

#include "Automaton.h"
class Id : public Automaton
{
public:
    Id() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);

    bool check_for_sign(bool alpha_bool, char current_index);
};


#endif