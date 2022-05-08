#pragma once

#include "lex.h"
#include "scanner.h"
#include <iostream>

class RPN {
    typedef Lex* lex;
    int size;
    lex* content;
public:
    RPN();    

    void    push_back(lex);    
    int     get_size() const;

    lex& operator[] (unsigned);
    friend std::ostream& operator<<(std::ostream&, RPN&);
};
