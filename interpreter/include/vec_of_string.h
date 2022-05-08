#pragma once

#include <string>
#include <cassert>

class VecOfString
{
    unsigned     size;
    std::string* content;

public:
    VecOfString();
    ~VecOfString();
    VecOfString(const std::initializer_list<std::string> &);

    void    push_back(std::string);
    int     find(std::string);
    int     get_size() const;

    std::string operator[](unsigned);
};