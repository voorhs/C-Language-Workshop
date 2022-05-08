#pragma once

#include "lex.h"
#include "ident.h"
#include "scanner.h"
#include <stack>
#include "parser.h"

#include "string.h"

enum data_type
{
    INT, BOOL, STRING
};

class ex_stack
{
    std::stack<int>         st_int;
    std::stack<bool>        st_bool;
    std::stack<std::string> st_string;

    std::stack<data_type>   st;

    int size;

public:
    ex_stack();

    bool is_empty() const;

    void push(int);
    void push(bool);
    void push(std::string);
    
    int         ipop();
    bool        bpop();
    std::string spop();

    void clear();
};

class Executer
{
    ex_stack st;

public:
    void perform(RPN&);
};

char* cat(const char*, const char*);

void read_str(char*&);
