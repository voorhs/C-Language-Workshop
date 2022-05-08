#include "lex.h"

/* Lex */

VecOfString Lex::TW =
{
    "", "and", "continue", "false", "if", "int",
    "not", "or", "program", "read", "bool", "string", "true", "while", "write"
};

VecOfString Lex::TD =
{
    "", ";", ",", "(", ")", "{", "}", "=", "==", "!=",
    "<", ">", "<=", ">=", "+", "-", "*", "/"
};

Lex::Lex(type_of_lex t) :
    type(t)
{
}

unsigned Lex::get_index() const
{
    return static_cast<unsigned>(type);
}

type_of_lex Lex::get_type() const
{
    return type;
}

void Lex::set_type(type_of_lex t) {
    type = t;
}

/* keyWord_lex */

keyWord_lex::keyWord_lex(unsigned shift)
{
    type = static_cast<type_of_lex>(shift);    
}

unsigned keyWord_lex::get_index() const
{
    return static_cast<unsigned>(type);
}

/* delimiter_lex */

delimiter_lex::delimiter_lex(unsigned shift)    
{
    type = static_cast<type_of_lex>(LEX_FIN + shift);    
}

unsigned delimiter_lex::get_index() const
{
    return static_cast<unsigned>(type - LEX_FIN);
}

delimiter_lex::delimiter_lex(type_of_lex t)
{
    type = t;
}

/* operation_lex */

operation_lex::operation_lex(type_of_lex t, type_of_lex dt)
{
    int shift;
    if (dt = LEX_INT)
        shift = 0;
    else if (dt = LEX_BOOL)
        shift = 13;
    else if (dt = LEX_STRING)
        shift = 16;
    else if (dt = LEX_INT_LITER)
        shift = 4;
    
    type = static_cast<type_of_lex>(t + shift);
}

/* RPN_lex */

RPN_lex::RPN_lex(type_of_lex t, unsigned u) :
    Lex(t), value(u)
{
}

int RPN_lex::get_int() const
{
    return value;
}

/* literal_lex */

literal_lex::literal_lex(int value) :
    Lex(LEX_INT_LITER)
{
    ivalue = value;
}

literal_lex::literal_lex(std::string value) :
    Lex(LEX_STRING_LITER)
{
    svalue = value;
}

literal_lex::literal_lex(bool value) :
    Lex(LEX_BOOL_LITER)
{
    bvalue = value;
}

int literal_lex::get_int() const
{
    return ivalue;
}

std::string literal_lex::get_string() const
{
    return svalue;
}

bool literal_lex::get_bool() const
{
    return bvalue;
}
