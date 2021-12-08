#ifndef Q_mark_H
#define Q_mark_H

#include "Automaton.h"
class Q_mark : public Automaton
{
public:
    Q_mark() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif