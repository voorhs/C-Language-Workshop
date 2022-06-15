#include "ident.h"

Ident::Ident() :
    assign(false), declare(false)
{
}

void Ident::set_name(std::string n)
{
	name = n;
}

std::string Ident::get_name() const
{
    return name;
}

void Ident::set_declared()
{
    declare = true;
}
bool Ident::is_declared() const
{
    return declare;
}

void Ident::set_assigned()
{
    assign = true;
}

bool Ident::is_assigned() const
{
    return assign;
}

void Ident::set_type(id_type t)
{
    type = t;
}

type_of_lex Ident::get_type() const
{
    if (type == ID_BOOL)
        return LEX_BOOL;

    if (type == ID_INT)
        return LEX_INT;

    if (type == ID_STRING)
        return LEX_STRING;

    return LEX_NULL;
}

void Ident::set_int(int v)
{
    ivalue = v;
}

int Ident::get_int() const
{
    return ivalue;
}

void Ident::set_bool(bool v)
{
    bvalue = v;
}

bool Ident::get_bool() const
{
    return bvalue;
}

void Ident::set_string(std::string buf)
{
    svalue = buf;
}

std::string Ident::get_string() const
{
    return svalue;
}
