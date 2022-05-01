#pragma once

#include "lex.h"
#include "ident.h"
#include "scanner.h"
#include "poliz.h"
#include <iostream>
#include <stack>

class Parser {
    Lex*         CL;     // current lexeme
    type_of_lex CT;     // type of CL

    Scanner scan;
    bool lvalue;
    std::stack<type_of_lex>    st;
    std::stack<int>             continue_st;    

    /* utilities */
    void push_const();
    void gl();

    /* recursive procedures */
    void P();
    void D1();
    void D(type_of_lex);
    void B();
    void S();
    void E();
    void O();
    void A();
    void L();
    void E1();
    void T();
    void N();
    void F();

    /* checking semantic conditions */
    void check_id();
    void check_read();
    void assertUndeclared(std::string, type_of_lex);
    void eq_type();
    void check_O();
    void check_A();
    void check_L();
    void check_E1();
    void check_T();
    void check_N();

public:
    Parser(const char*);
    RPN prog;
    void analyze();
};