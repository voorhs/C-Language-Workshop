#include "parser.h"

Parser::Parser(const char* buf) : scan(buf) {}

void Parser::gl() {
    CL = scan.get_lex();
    CT = CL->get_type();
    std::cout << CL << std::endl;
}

void Parser::P()
{
    if (CT == LEX_PROGRAM)
        gl();
    else
        throw CL;

    if (CT == LEX_LBRACE)
    {
        gl();
        D1();
        B();
    }
    else throw CL;

    if (CT == LEX_RBRACE)
        gl();
    else throw CL;

    if (CT == LEX_FIN)
        {}
    else throw CL;
}

void Parser::D1()
{
    while (CT == LEX_INT || CT == LEX_BOOL || CT == LEX_STRING)
    {        
        D(CT);

        if (CT == LEX_SEMICOLON)
            gl();
        else
            throw CL;
    }
}

void Parser::D(type_of_lex DT)
{    
    Lex* CID;    // current ID which might be an lvalue expression

    do
    {
        gl();
        if (CT == LEX_ID)
        {
            CID = CL;
            assertUndeclared(CID->get_string(), DT);
            st.push(DT);
            gl();
        }
        else throw CL;

        if (CT == LEX_ASSIGN)
        {
            st.push(CT);
            gl();

            if (CT == LEX_INT_LITER || CT == LEX_BOOL_LITER || CT == LEX_STRING_LITER)
            {
                prog.push_back(new RPN_lex(POLIZ_ADDRESS, CID->get_int()));         // shall we change this constructor?
                prog.push_back(CL);
                push_const();
                eq_type();
                prog.push_back(new delimiter_lex(LEX_SEMICOLON));     /// ???? why ????
                gl();
            }
            else throw CL;
        }
        else st.pop();
    }
    while (CT == LEX_COMMA);
}

void Parser::B() {
    while ((CT != LEX_RBRACE) && (CT != LEX_FIN))
        S();
}

void Parser::S()
{
    if (CT == LEX_IF)
    {        
        gl();

        if (CT == LEX_LPAREN) {
            gl();
            E();
            st.pop();
            prog.push_back(new RPN_lex(POLIZ_LABEL));   // label to else-branch
            prog.push_back(new RPN_lex(POLIZ_FGO));     // of the conditional operator
        }
        else throw CL;

        if (CT == LEX_RPAREN) {
            gl();
            S();
            prog.push_back(new RPN_lex(POLIZ_LABEL));   // way out label
            prog.push_back(new RPN_lex(POLIZ_GO));
        }
        else throw CL;

    }
    else if (CT == LEX_WHILE)
    {
        int continue_l;                     // how is it used?
        gl();
        if (CT == LEX_LPAREN)
        {
            gl();
            
            continue_l = prog.get_size();           // label of return to next iteration
            continue_st.push(continue_l);       
            
            E();
            
            st.pop();
            prog.push_back(new RPN_lex(POLIZ_LABEL));           // way out label
            prog.push_back(new RPN_lex(POLIZ_FGO));             // in case condition is false
        }
        else throw CL;

        if (CT == LEX_RPAREN)
        {
            gl();
            S();

            prog.push_back(new RPN_lex(POLIZ_LABEL, continue_l));   // label to the next iteration
            prog.push_back(new RPN_lex(POLIZ_GO));            
        }
        else throw CL;

    }
    else if (CT == LEX_CONTINUE)
    {
        if (continue_st.empty())
            throw "continue outside the loop";

        int continue_l = continue_st.top();
                         continue_st.pop();

        continue_st.push(continue_l);

        prog.push_back(new RPN_lex(POLIZ_LABEL, continue_l));
        prog.push_back(new RPN_lex(POLIZ_GO));

        gl();

        if (CT == LEX_SEMICOLON)
            gl();
        else throw CL;

    }
    else if (CT == LEX_READ) {
        gl();

        if (CT == LEX_LPAREN)
            gl();
        else throw CL;

        if (CT == LEX_ID)
        {
            check_id();
            check_read();

            prog.push_back(new RPN_lex(POLIZ_ADDRESS, CL->get_int()));
            prog.push_back(new keyWord_lex(LEX_READ));

            gl();
        }
        else throw CL;

        if (CT == LEX_RPAREN)
            gl();
        else throw CL;

        if (CT == LEX_SEMICOLON)
            gl();
        else throw CL;
    }
    else if (CT == LEX_WRITE)
    {
        gl();

        if (CT == LEX_LPAREN)
            gl();
        else throw CL;

        E();
        st.pop();
        prog.push_back(new keyWord_lex(LEX_WRITE));

        while (CT == LEX_COMMA)
        {
            gl();
            E();

            st.pop();
            prog.push_back(new keyWord_lex(LEX_WRITE));
        }

        if (CT == LEX_RPAREN)
            gl();

        else throw CL;

        if (CT == LEX_SEMICOLON)
            gl();

        else throw CL;
    }
    else if (CT == LEX_LBRACE)
    {
        gl();
        B();

        if (CT == LEX_RBRACE)
            gl();
        else throw CL;
    }
    else
    {
        E();
        st.pop();

        prog.push_back(new delimiter_lex(LEX_SEMICOLON));

        if (CT == LEX_SEMICOLON)
            gl();
        else throw CL;
    }
}

void Parser::E()
{
    lvalue = true;
    O();

    if (CT == LEX_ASSIGN)
    {
        if (!lvalue)
            throw "Not l_value expression";

        st.push(CT);

        gl();
        E();
        eq_type();
    }
}

void Parser::O()
{
    A();

    while (CT == LEX_OR) {
        lvalue = false;

        st.push(CT);
        gl();
        A();
        check_O();
    }
}

void Parser::A()
{
    L();

    while (CT == LEX_AND)
    {
        lvalue = false;
        st.push(CT);
        gl();
        L();
        check_A();
    }
}

void Parser::L()
{
    E1();

    while (CT == LEX_EQ || CT == LEX_NEQ || CT == LEX_GTR || CT == LEX_GEQ || CT == LEX_LSS || CT == LEX_LEQ) {
        lvalue = false;
        st.push(CT);
        gl();
        E1();
        check_L();
    }
}

void Parser::E1()
{
    T();

    while (CT == LEX_PLUS || CT == LEX_MINUS) {
        lvalue = false;
        st.push(CT);
        gl();
        T();
        check_E1();
    }
}

void Parser::T() {
    N();
    while (CT == LEX_TIMES || CT == LEX_SLASH) {
        lvalue = false;
        st.push(CT);
        gl();
        N();
        check_T();
    }
}

void Parser::N()
{
    if (CT == LEX_NOT || CT == LEX_PLUS || CT == LEX_MINUS)
    {
        lvalue = false;
        st.push(CT);
        gl();
        N();
        check_N();
    }
    else F();
}

void Parser::F() {
    if (CT == LEX_LPAREN)
    {
        lvalue = false;
        gl();
        E();

        if (CT == LEX_RPAREN)
            gl();
        
        else throw CL;
    }
    else if (CT == LEX_INT_LITER || CT == LEX_BOOL_LITER || CT == LEX_STRING_LITER)
    {
        lvalue = false;
        push_const();
        prog.push_back(CL);
        gl();
    }
    else if (CT == LEX_ID)
    {
        check_id();

        Ident id = Scanner::TID[CL->get_int()];
        st.push(id.get_type()); 
        
        prog.push_back(new RPN_lex(POLIZ_ADDRESS, CL->get_int()));
        
        gl();
    }
    else throw CL;
}

void Parser::analyze() {
    gl();
    P();
    std::cout << "SUCCESS" <<std::endl;
}

void Parser::push_const()
{
    if (CT == LEX_INT_LITER)
        st.push(LEX_INT);

    else if (CT == LEX_BOOL_LITER)
        st.push(LEX_BOOL);

    else if (CT == LEX_STRING_LITER)
        st.push(LEX_STRING);

    else
        throw "bad convertion literal to data type";
}

void Parser::check_id()
{
    int index = Scanner::TID.find(CL->get_string());
    Ident id = Scanner::TID[index];

    if (!id.get_declare())
        throw "ID is not declared";
}

void Parser::check_read()
{
    int index = Scanner::TID.find(CL->get_string());
    Ident id = Scanner::TID[index];

    if (id.get_type() == LEX_BOOL)
        throw "you can't read boolean variable";
}

void Parser::assertUndeclared(std::string name, type_of_lex DT)
{
    int index = Scanner::TID.find(name);        // should we code custom hash-table?
    Ident& id = Scanner::TID[index];

    if (id.get_declare())
        throw "ID has been already declared!";

    else
    {
        id.set_declare();

        id_type res;
        if (DT == LEX_INT)
            res = ID_INT;
        else if (DT == LEX_BOOL)
            res = ID_BOOL;
        else if (DT == LEX_STRING)
            res = ID_STRING;

        id.set_type(res);
    }
}

void Parser::eq_type()
{
    type_of_lex r_value = st.top();     st.pop();
    type_of_lex operation = st.top();   st.pop();
    type_of_lex l_value = st.top();     st.pop();

    if (l_value != r_value)
        throw "you can't use several data types within one equation";

    if (l_value == LEX_INT)
    {
        st.push(l_value);
        prog.push_back(new operation_lex(operation, LEX_INT));
    }
    else if (l_value == LEX_BOOL)
    {
        st.push(l_value);
        prog.push_back(new operation_lex(operation, LEX_BOOL));
    }
    else if (l_value == LEX_STRING)
    {     
        st.push(l_value);
        prog.push_back(new operation_lex(operation, LEX_STRING));
    }
}

void Parser::check_O() {

    type_of_lex operand1 = st.top(); st.pop();
    type_of_lex operation = st.top(); st.pop();
    type_of_lex operand2 = st.top(); st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT)
    {
        st.push(LEX_INT);
        prog.push_back(new delimiter_lex(operation));
    }
    else throw "Wrong types in operation";
}

void Parser::check_A() {

    type_of_lex operand1 = st.top(); st.pop();
    type_of_lex operation = st.top(); st.pop();
    type_of_lex operand2 = st.top(); st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT)
    {
        st.push(LEX_INT);
        prog.push_back(new delimiter_lex(operation));
    }
    else throw "Wrong types in operation";
}

void Parser::check_L() {

    type_of_lex operand1 = st.top(); st.pop();
    type_of_lex operation = st.top(); st.pop();
    type_of_lex operand2 = st.top(); st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT)
    {
        st.push(LEX_INT);
        prog.push_back(new delimiter_lex(operation));
    }
    else if (operand1 == LEX_STRING && operand2 == LEX_STRING)
    {
        st.push(LEX_INT);
        prog.push_back(new operation_lex(operation, LEX_STRING));
    }
    else if (operand1 == LEX_STRING || operand2 == LEX_STRING)
        throw "Wrong types in operation";
    else
    {
        st.push(LEX_INT);
        prog.push_back(new operation_lex(operation, LEX_BOOL));
    }
}

void Parser::check_E1() {

    type_of_lex operand1 = st.top(); st.pop();
    type_of_lex operation = st.top(); st.pop();
    type_of_lex operand2 = st.top(); st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT)
    {
        st.push(LEX_INT);
        prog.push_back(new delimiter_lex(operation));
    }
    else if (operand1 == LEX_STRING && operand2 == LEX_STRING)
    {
        if (operation != LEX_PLUS)
         throw "Wrong types in operation";

        st.push(LEX_STRING);
        prog.push_back(new operation_lex(operation, LEX_STRING));
    }
    else if (operand1 == LEX_STRING || operand2 == LEX_STRING)
        throw "Wrong types in operation";

    else
    {
        st.push(LEX_BOOL);
        prog.push_back(new operation_lex(operation, LEX_BOOL));
    }
}

void Parser::check_T() {

    type_of_lex operand1 = st.top(); st.pop();
    type_of_lex operation = st.top(); st.pop();
    type_of_lex operand2 = st.top(); st.pop();

    if (operand1 == LEX_INT && operand2 == LEX_INT)
    {
        st.push(LEX_INT);
        prog.push_back(new delimiter_lex(operation));
    }
    else if (operand1 == LEX_STRING || operand2 == LEX_STRING)
        throw "Wrong types in operation";

    else
    {
        st.push(LEX_BOOL);
        prog.push_back(new operation_lex(operation, LEX_BOOL));
    }
}

void Parser::check_N() {

    type_of_lex operand = st.top(); st.pop();
    type_of_lex operation = st.top(); st.pop();

    if (operand == LEX_STRING)
        throw "Wrong types in operation";

    else if (operation == LEX_NOT)
    {
        if(operand != LEX_INT) throw "Wrong types in operation";
        st.push(LEX_INT);
        prog.push_back(new delimiter_lex(operation));
    }
    else
    {
        if(operand == LEX_INT)
        {
            st.push(LEX_INT);
            prog.push_back(new operation_lex(operation, LEX_INT_LITER));
        }
    }
}