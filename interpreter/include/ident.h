#pragma once

#include "lex.h"

#include <cstring>
#include <string>

enum id_type
{
    ID_INT,
    ID_STRING,
    ID_BOOL,
};

class Ident
{
    std::string name;

    bool assign,
         declare;

    id_type type;

    int         ivalue;
    bool        bvalue;
    std::string svalue;

public:
    Ident();

    void        set_name(std::string n);
    std::string get_name() const;

    void        set_declared();
    bool        is_declared() const;

    void        set_assigned();
    bool        is_assigned() const;

    void        set_type(id_type t);
    type_of_lex get_type() const;

    void        set_int(int v);
    int         get_int() const;

    void        set_bool(bool v);
    bool        get_bool() const;

    void        set_string(std::string buf);
    std::string get_string() const;
};