#include "ident.h"

Ident::Ident() : assign(false), declare(false) {};

void Ident::set_name(std::string n)
{
	name = n;
}

std::string Ident::get_name() const { return name; }

void Ident::set_declare() { declare = true; }
bool Ident::get_declare() const { return declare; }

void Ident::set_assign() { assign = true; }
bool Ident::get_assign() const { return assign; }

void Ident::set_type(id_type t) { type = t; }

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

void Ident::set_int_value(int v) { int_value = v; }
int Ident::get_int_value() const { return int_value; }

void Ident::set_bool_value(bool v) { bool_value = v; }
bool Ident::get_bool_value() const { return bool_value; }

void Ident::set_str_value(char* buf) { str_value = new char[strlen(buf) + 1]; strcpy(str_value, buf); }
char* Ident::get_str_value() const { return str_value; }
