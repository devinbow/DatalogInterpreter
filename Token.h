#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    // TODO: add the other types of tokens
    EOF_TYPE,
    UNDEFINED
    //EOF is reserved keyword, used EOF_TYPE
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    std::string actual_value;
    int line_starts = 0;
    TokenType type;
    std::string description = "";

    //TokenType
    //^^ for example, print Colon instead of 0 for the enum.
    //^^ switch cases


public:
    Token(TokenType type, std::string description, int line) { this->type = type; actual_value = description;  line_starts = line; }
    TokenType getType() { return type; }
    std::string getDescription() { return actual_value; }
    int getLine_s() { return line_starts; }
    std::string tokenToString(TokenType type);

    // TODO: add other needed methods
    //toString
    void ToString(TokenType type, std::string actual_value, int line_starts);
};

#endif // TOKEN_H

