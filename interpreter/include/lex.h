#pragma once

#include "vec_of_string.h"
#include <iostream>
#include <cstring>
#include <string>

enum type_of_lex {

/* reserved (key) words */

    LEX_NULL,       LEX_AND,        LEX_CONTINUE,   LEX_FALSE,      LEX_IF,             /*  4 */
    LEX_INT,        LEX_NOT,        LEX_OR,         LEX_PROGRAM,    LEX_READ,           /*  9 */
    LEX_BOOL,       LEX_STRING,     LEX_TRUE,       LEX_WHILE,      LEX_WRITE,          /* 14 */

/* delimiters and math signs */

    LEX_FIN,        LEX_SEMICOLON,  LEX_COMMA,      LEX_LPAREN,     LEX_RPAREN,         /* 19 */
    LEX_LBRACE,     LEX_RBRACE,     LEX_ASSIGN,     LEX_EQ,         LEX_NEQ,            /* 24 */
    LEX_LSS,        LEX_GTR,        LEX_LEQ,        LEX_GEQ,        LEX_PLUS,           /* 29 */
    LEX_MINUS,      LEX_TIMES,      LEX_SLASH,                                          /* 32 */


/* implicit signs (type-wise operations) */

    LEX_U_PLUS,     LEX_U_MINUS,    LEX_B_ASSIGN,   LEX_B_EQ,       LEX_B_NEQ,          /* 37 */
    LEX_S_ASSIGN,   LEX_S_EQ,       LEX_S_NEQ,      LEX_S_LSS,      LEX_S_GTR,          /* 42 */
    LEX_S_LEQ,      LEX_S_GEQ,      LEX_S_PLUS,     LEX_INT_LITER,  LEX_STRING_LITER,   /* 47 */
    LEX_BOOL_LITER, LEX_ID,                                                             /* 49 */

/* reverted polish notation */

    POLIZ_LABEL,    POLIZ_ADDRESS,  POLIZ_GO,       POLIZ_FGO,                          /* 62 */

};

//// base class 'Lex' ////

class Lex
{
protected:
    type_of_lex type;    

    static VecOfString TW;  // table of key words
    static VecOfString TD;  // table of delimiters and math operators
    
public:
    Lex(type_of_lex t = LEX_NULL);    

    virtual unsigned    get_index() const;
    type_of_lex get_type() const;
    void        set_type(type_of_lex);

    virtual int         get_int() const { return 0; }
    virtual std::string get_string() const  { return 0; }
    virtual bool        get_bool() const  { return 0; }

    friend class Scanner;
    friend std::ostream& operator<<(std::ostream& out, Lex* l);
};

//// first group of derived classes ////

struct keyWord_lex: Lex
{
    keyWord_lex(unsigned);
    unsigned get_index() const;
};

struct delimiter_lex: Lex
{
    delimiter_lex(unsigned);    
    delimiter_lex(type_of_lex t);
    unsigned get_index() const;
};

struct operation_lex: Lex
{
    operation_lex(type_of_lex, type_of_lex);
};

//// second group of derived classes ////

class literal_lex: public Lex {
    int         ivalue;         // for LEX_INT_LITER
    std::string svalue;         // for LEX_STRING_LITER
    bool        bvalue;         // for LEX_BOOL_LITER
public:    
    literal_lex(int);
    literal_lex(std::string);
    literal_lex(bool);

    int         get_int() const;
    std::string get_string() const;
    bool        get_bool() const;
};

class RPN_lex: public Lex {
    unsigned value;
public:
    RPN_lex(type_of_lex, unsigned = 0);
    int get_int() const;
};