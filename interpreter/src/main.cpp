#include "lex.h"
#include "parser.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        Parser pars(argv[1]);
        cout << "-== Lexical + Syntactical + Semantical Analysis ==-\n\ttype code\ttype\t\tlexeme\n\n";
        pars.analyze();
        cout << "\n\t-== Reverted Polish Notation: ==-\n\ttype code\ttype\t\tlexeme\n" << pars.prog << "SUCCESS" << endl;
        return 0;
    }
    catch (char c)
    {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex* l)
    {
        cout << "unexpected lexeme " << l << endl;
        return 1;
    }
    catch (const char* str)
    {
        cout << str << endl;
        return 1;
    }
    catch (...)
    {
        cout << "unexpected error" << endl;
        return 1;
    }
}
