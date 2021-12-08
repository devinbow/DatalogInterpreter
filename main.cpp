#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Database.h"
#include <fstream>
#include <iostream>
#include <cctype>
//lexer.h has token vector

int main(int argc, char** argv) {
    std::string filename = argv[1];
    std::ifstream ifs(filename);
    std::string input;
    std::string parse_input;


    while (!ifs.eof())
    {
        getline(ifs, input);
        parse_input += input + "\n";
    }
    Lexer* lexer = new Lexer();
    lexer->Run(parse_input);
    Parser parser = Parser();
    //EXPERIMENT: CURRENTLY DELETING ORIGINAL TOKEN LIST. IF BECOMES AN ISSUE, THEN MAKE getTokenList SEND A COPY.
    parser.parse(lexer->getTokenList());

   // lexer->toString();

   // delete lexer;


    //parser contains the datalogProgram
    Database database = Database();
    Interpreter inter = Interpreter(parser.getProgram(), database);
    inter.inter_work();

    return 0;
}