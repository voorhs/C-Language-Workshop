#pragma once

#include "tid.h"
#include "lex.h"

#include <iostream>
#include <cmath>

class Scanner {
    FILE* fp;
    char c;
    static const char* TW[]; static const char* TD[];
    int look(const char* buf, const char** list);
    void getchar();

public:
    static Table_Ident TID;
    Scanner(const char* program);
    Lex get_lex();
    friend std::ostream& operator<<(std::ostream& out, Lex l);
};
