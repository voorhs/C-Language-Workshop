#pragma once

#include "lex.h"

#include <cstring>
#include <string>

enum id_type {
    ID_INT, ID_STRING, ID_BOOL,
};

class Ident {
    std::string name;
    
    bool    declare,
            assign;
    
    id_type type;
    
    int     int_value;
    bool    bool_value;
    char*   str_value;

public:
    Ident();

    void set_name(std::string n);
    std::string get_name() const;

    void set_declare();
    bool get_declare() const;

    void set_assign();
    bool get_assign() const;

    void set_type(id_type t);
    type_of_lex get_type() const;

    void set_int_value(int v);
    int get_int_value() const;

    void set_bool_value(bool v);
    bool get_bool_value() const;

    void set_str_value(char* buf);
    char* get_str_value() const;
};