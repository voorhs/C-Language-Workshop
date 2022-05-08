#include "executer.h"

void Executer::perform(RPN& poliz)
{
    // std::cout << "\n\t-== EXECUTE ==-" << std::endl;

    int size = poliz.get_size(),
        index = 0;

    while (index < size) {

        Lex* el = poliz[index++];

        switch (el->get_type())             // put values to stack
        {           
            case LEX_INT_LITER:
            
                st.push(el->get_int());
                break;
            
            case LEX_STRING_LITER:
            
                st.push(el->get_string());
                break;

            case LEX_BOOL_LITER:

                st.push(el->get_bool());
                break;
            
            case POLIZ_ADDRESS: case POLIZ_LABEL:

                st.push(el->get_int());
                break;            

            case LEX_ID:
            {
                int i = el->get_int();

                if (!Scanner::TID[i].is_assigned())
                    throw "ID is not assigned";

                type_of_lex type = Scanner::TID[i].get_type();
                if (type == LEX_INT)
                    st.push(Scanner::TID[i].get_int());

                else if (type == LEX_BOOL)
                    st.push(Scanner::TID[i].get_bool());

                else if (type == LEX_STRING)
                    st.push(Scanner::TID[i].get_string());

                break;
            }
            case LEX_ASSIGN:                // Assign operations
            {
                int op = st.ipop(),
                    i  = st.ipop();

                Scanner::TID[i].set_int(op);
                Scanner::TID[i].set_assigned();
                st.push(Scanner::TID[i].get_int());

                // std::cout << index << ' ' << Scanner::TID[i].get_name() << " <- " << op << std::endl;

                break;
            }
            case LEX_B_ASSIGN:
            {
                bool op = st.bpop();
                int   i = st.ipop();

                Scanner::TID[i].set_bool(op);
                Scanner::TID[i].set_assigned();
                st.push(Scanner::TID[i].get_bool());

                // std::cout << index << ' ' << Scanner::TID[i].get_name() << " <- " << op << std::endl;

                break;
            }
            case LEX_S_ASSIGN:
            {
                std::string op = st.spop();
                int          i = st.ipop();

                Scanner::TID[i].set_string(op);
                Scanner::TID[i].set_assigned();
                st.push(Scanner::TID[i].get_string());

                // std::cout << index << ' ' << Scanner::TID[i].get_name() << " <- " << op << std::endl;

                break;
            }

            case LEX_EQ:                    // Comparison operations
            {
                int op1 = st.ipop(),
                    op2 = st.ipop();

                st.push(op1 == op2);

                // std::cout << index << ' ' << op1 << " == " << op2 << std::endl;
                break;
            }
            case LEX_B_EQ:
            {
                bool op1 = st.bpop(),
                     op2 = st.bpop();

                st.push(op1 == op2);

                // std::cout << index << ' ' << op1 << " == " << op2 << std::endl;
                break;
            }
            case LEX_S_EQ:
            {
                std::string op1 = st.spop(),
                            op2 = st.spop();                

                st.push(op1 == op2);

                // std::cout << index << ' ' << op1 << " == " << op2 << std::endl;
                break;
            }
            case LEX_NEQ:
            {
                int op1 = st.ipop(),
                    op2 = st.ipop();

                st.push(op1 != op2);

                // std::cout << index << ' ' << op1 << " != " << op2 << std::endl;
                break;
            }
            case LEX_B_NEQ:
            {
                bool op1 = st.bpop(),
                     op2 = st.bpop();

                st.push(op1 != op2);

                // std::cout << index << ' ' << op1 << " != " << op2 << std::endl;
                break;
            }
            case LEX_S_NEQ:
            {
                std::string op1 = st.spop(),
                            op2 = st.spop();                            

                st.push(op1 != op2);

                // std::cout << index << ' ' << op1 << " != " << op2 << std::endl;
                break;
            }
            case LEX_LSS:
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 < op2);

                // std::cout << index << ' ' << op1 << " < " << op2 << std::endl;
                break;
            }
            case LEX_S_LSS:
            {
                std::string op2 = st.spop(),
                            op1 = st.spop();                

                st.push(op1 < op2);

                // std::cout << index << ' ' << op1 << " < " << op2 << std::endl;
                break;
            }
            case LEX_GTR:
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 > op2);

                // std::cout << index << ' ' << op1 << " > " << op2 << std::endl;
                break;
            }            
            case LEX_S_GTR:
            {
                std::string op2 = st.spop(),
                            op1 = st.spop();                

                st.push(op1 > op2);

                // std::cout << index << ' ' << op1 << " > " << op2 << std::endl;
                break;
            }
            case LEX_LEQ:
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 <= op2);

                // std::cout << index << ' ' << op1 << " <= " << op2 << std::endl;
                break;
            }            
            case LEX_S_LEQ:
            {
                std::string op2 = st.spop(),
                            op1 = st.spop();                

                st.push(op1 <= op2);

                // std::cout << index << ' ' << op1 << " <= " << op2 << std::endl;
                break;
            }
            case LEX_GEQ:
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 >= op2);

                // std::cout << index << ' ' << op1 << " >= " << op2 << std::endl;
                break;
            }
            case LEX_S_GEQ:
            {
                std::string op2 = st.spop(),
                            op1 = st.spop();                

                st.push(op1 >= op2);

                // std::cout << index << ' ' << op1 << " >= " << op2 << std::endl;
                break;
            }
            case LEX_PLUS:              // Arithmetic operations
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 + op2);

                // std::cout << index << ' ' << op1 << " + " << op2 << std::endl;
                break;
            }
            case LEX_MINUS:
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 - op2);

                // std::cout << index << ' ' << op1 << " - " << op2 << std::endl;
                break;
            }
            case LEX_TIMES:
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 * op2);

                // std::cout << index << ' ' << op1 << " * " << op2 << std::endl;
                break;
            }
            case LEX_SLASH:
            {
                int op2 = st.ipop(),
                    op1 = st.ipop();

                st.push(op1 / op2);

                // std::cout << index << ' ' << op1 << " / " << op2 << std::endl;
                break;
            }
            case LEX_U_PLUS:
            {
                // int op = st.ipop();
                // st.push(op);
                //std::cout << index << ' ' << int_operand1 << std::endl;

                break;
            }
            case LEX_U_MINUS:
            {
                int op = st.ipop();
                st.push(-op);

                // std::cout << index << ' ' << "unary -" << op << std::endl;
                break;
            }            
            case LEX_S_PLUS:
            {
                std::string op2 = st.spop(),
                            op1 = st.spop();

                st.push(op1 + op2);

                // std::cout << index << ' ' << op1 << " + " << op2 << std::endl;
                break;
            }
            case LEX_OR:                    // Logic operations
            {
                bool op2 = st.bpop(),
                     op1 = st.bpop();

                st.push(op1 || op2);

                // std::cout << index << ' ' << op1 << " || " << op2 << std::endl;
                break;
            }
            case LEX_AND:
            {
                bool op2 = st.bpop(),
                     op1 = st.bpop();

                st.push(op1 && op2);

                // std::cout << index << ' ' << op1 << " && " << op2 << std::endl;
                break;
            }
            case LEX_NOT:
            {
                int op = st.ipop();
                st.push(!op);

                // std::cout << index << ' ' << "!" << op << std::endl;
                break;
            }    
            case POLIZ_GO:                  // Transer

                index = st.ipop();

                // std::cout << index << ' ' << "goto " << index << std::endl;

                break;

            case POLIZ_FGO:
            {
                int     label = st.ipop();
                bool    condition = st.bpop();

                if(!condition)
                {
                    index = label;
                    // std::cout << index << ' ' << "goto " << index << std::endl;
                }

                break;
            }
            case LEX_READ:                      // I/O statements
            {
                int         i    = st.ipop();
                type_of_lex type = Scanner::TID[i].get_type();

                if (type == LEX_INT)
                {
                    int value;
                    std::cin >> value;

                    Scanner::TID[i].set_int(value);
                    Scanner::TID[i].set_assigned();                    
                }
                else if (type == LEX_STRING)
                {
                    std::string value;
                    std::cin >> value;
                    Scanner::TID[i].set_string(value);
                    Scanner::TID[i].set_assigned();                    
                }

                // std::cout << index << ' ' << "read" << std::endl;
                break;
            }
            case LEX_WRITE:

                std::cout << st.ipop() << std::endl;

                break;

            case LEX_B_WRITE:

                std::cout << (st.bpop() ? "true" : "false") << std::endl;                

                break;

            case LEX_S_WRITE:

                std::cout << st.spop() << std::endl;

                break;

            case LEX_SEMICOLON:                 // clear execute stack top

                st.clear();
                // std::cout << "clear stack" << std::endl;
                break;

            default:

                throw "executer dumped";
        }
    }
}

ex_stack::ex_stack()
{   
}

void ex_stack::clear()
{
    if (!is_empty())
    {
        st.pop();
    }
}

bool ex_stack::is_empty() const
{
    return (st.empty());
}

void ex_stack::push (int v)
{
    st.push(INT);
    st_int.push(v);
}

void ex_stack::push(bool v)
{
    st.push(BOOL);
    st_bool.push(v);
}

void ex_stack::push(std::string v)
{
    st.push(STRING);
    st_string.push(v);
}

int ex_stack::ipop()
{
    assert(!is_empty());

    st.pop();

    int res = st_int.top();
              st_int.pop();

    return res;
}

bool ex_stack::bpop()
{
    assert(!is_empty());

    st.pop();

    bool res = st_bool.top();
               st_bool.pop();

    return res;
}

std::string ex_stack::spop()
{
    assert(!is_empty());

    st.pop();

    std::string res = st_string.top();
                      st_string.pop();

    return res;
}