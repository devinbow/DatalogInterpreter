#include <iostream>
#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "EOF_TYPE.h"
#include "Undefined.h"
#include "Add.h"
#include "Comma.h"
#include "Comment.h"
#include "Facts.h"
#include "Id.h"
#include "Left_paren.h"
#include "Multiply.h"
#include "Period.h"
#include "Q_mark.h"
#include "Queries.h"
#include "Right_paren.h"
#include "Rules.h"
#include "Schemes.h"
#include "String.h"
//isspace(char) will return true if space
//isalpha for if alphabet
//isnum for if number
int token_count = 0;
Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
   // for (unsigned int i = 0; i < automata.size(); i++) {
   //     delete automata[i];
  //  }
  //  for (unsigned int i = 0; i < tokens.size(); i++) {
   //     delete tokens[i];
  //  }
 //   automata.clear();
 //   tokens.clear();
    std::cout << "Total Tokens = " << token_count;
    
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new Add());
    automata.push_back(new Comma());
    automata.push_back(new Comment());
    automata.push_back(new Facts());
    automata.push_back(new Id());
    automata.push_back(new Left_paren());
    automata.push_back(new Multiply());
    automata.push_back(new Period());
    automata.push_back(new Q_mark());
    automata.push_back(new Queries());
    automata.push_back(new Right_paren());
    automata.push_back(new Rules());
    automata.push_back(new Schemes());
    automata.push_back(new String());
    automata.push_back(new EOF_TYPE());
    automata.push_back(new Undefined());
}

void Lexer::Run(std::string& input) {
    int line_number = 1;
    Token* newToken;

    while (input.size() > 0)
    {
        while (isspace(input[0]))
        {
            if (input[0] == '\n')
            {
                if (!empty(input.substr(1)))
                    line_number++;
            }
            input = input.substr(1);
        }
        int maxRead = 0;
        maxAutomata = automata[0];
        if (input.size() > 0)
        {
            for (Automaton* current_automata : automata) {
                int inputRead = current_automata->Start(input);
                if (inputRead > maxRead) {
                    if (current_automata->getType() == automata[6]->getType())
                    {
                        if (input.substr(0, 5) == "Facts" && is_not_alpha_check(input[5]))
                        {
                            maxRead = 5;
                            maxAutomata = automata[5];
                        }
                        else if (input.substr(0, 5) == "Rules" && is_not_alpha_check(input[5]))
                        {
                            maxRead = 5;
                            maxAutomata = automata[13];
                        }
                        else if (input.substr(0, 7) == "Schemes" && is_not_alpha_check(input[7]))
                        {
                            maxRead = 7;
                            maxAutomata = automata[14];
                        }
                        else if (input.substr(0, 7) == "Queries" && is_not_alpha_check(input[7]))
                        {
                            maxRead = 7;
                            maxAutomata = automata[11];
                        }
                        else
                        {
                            maxRead = inputRead;
                            maxAutomata = current_automata;
                        }
                    }
                    else
                    {
                        maxRead = inputRead;
                        maxAutomata = current_automata;
                    }
                }
            }

            if (maxRead > 0)
            {
                newToken = maxAutomata->CreateToken(input.substr(0, maxRead), line_number);
                line_number += maxAutomata->NewLinesRead();
                if (newToken->getType() != TokenType::COMMENT)
                {
                    token_count++;
                    tokens.push_back(newToken);
                }
            }
            else {
                maxRead = 1;
                newToken = automata.back()->CreateToken(input.substr(0, maxRead), line_number);
                token_count++;
                tokens.push_back(newToken);
            }

            if (!input.empty())
                input = input.substr(maxRead);
        }
    }
    int end_of_file = automata.size() - 2;
    newToken = automata[end_of_file]->CreateToken("", line_number);
    token_count++;
    tokens.push_back(newToken);
}