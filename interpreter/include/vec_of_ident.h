#pragma once

#include "ident.h"
#include <string>

class VecOfIdent
{
    int     size;
    Ident*  content;

public:
    VecOfIdent();
    ~VecOfIdent();

    void    push_back(Ident);
    int     find(std::string);
    int     get_size() const;

    Ident &operator[](unsigned);
};