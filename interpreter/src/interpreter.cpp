#include "inter.h"

Interpreter::Interpreter(const char* prog) :
    pars(prog)
{
}

int Interpreter::perform()
{
    try
    {
        std::cout << "-== Lexical + Syntactical + Semantical Analysis ==-\n\ttype code\ttype\t\tlexeme\n\n";
        pars.perform();
        std::cout << "\n\t-== Reverted Polish Notation: ==-\n\ttype code\ttype\t\tlexeme\n\n"
             << pars.program << "SUCCESS" << std::endl;
        exec.perform(pars.program);
        return 0;
    }
    catch (char c)
    {
        std::cout << "unexpected symbol " << c << std::endl;
        return 1;
    }
    catch (Lex *l)
    {
        std::cout << "unexpected lexeme " << l << std::endl;
        return 1;
    }
    catch (const char *str)
    {
        std::cout << str << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "unexpected error" << std::endl;
        return 1;
    }
}
