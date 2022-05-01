#pragma once

#include "lex.h"
#include "ident.h"
#include "vec_of_string.h"
#include "vec_of_ident.h"

#include <iostream>
#include <string>
#include <cmath>

class Scanner {
    FILE* fp;           

public:
    Scanner(const char* fileName);

    static VecOfIdent TID;
    void addID(std::string name);
    
    Lex* get_lex();

    friend class id_lex;
    friend std::ostream& operator<<(std::ostream& out, Lex* l);
};

class id_lex: public Lex {
    std::string name;
public:
    id_lex(std::string);

    int         get_int() const;
    std::string get_string() const;
};