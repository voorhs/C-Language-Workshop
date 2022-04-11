#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

enum type_of_lex {
    LEX_NULL, /*0*/
    LEX_AND, LEX_CONTINUE, LEX_FALSE, LEX_IF, LEX_INT, /*5*/
    LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_BOOL, LEX_STRING, LEX_TRUE, LEX_WHILE, LEX_WRITE, /*14*/
    LEX_FIN, /*15*/
    LEX_SEMICOLON, LEX_COMMA, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_LBRACE, LEX_RBRACE, LEX_EQ, LEX_LSS, /*24*/
    LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, /*32*/
    LEX_INT_CONST, LEX_STRING_CONST, /*34*/
    LEX_ID, /*35*/
    POLIZ_LABEL, /*36*/
    POLIZ_ADDRESS, /*37*/
    POLIZ_GO, /*38*/
    POLIZ_FGO  /*39*/
};

class Lex {
    type_of_lex type;
    int     int_value;
    bool    bool_value;
    char*   str_value;

public:

    Lex(type_of_lex t = LEX_NULL);
    Lex(type_of_lex t, int v);
    Lex(type_of_lex t, bool v);
    Lex(type_of_lex t, char* buf);

    type_of_lex get_type() const;

    int     get_int_value() const;
    bool    get_bool_value() const;
    char*   get_str_value() const;

    friend std::ostream& operator<<(std::ostream& out, Lex l);
};
