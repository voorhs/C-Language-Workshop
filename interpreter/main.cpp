#include <iostream>

#include "lex.h"
#include "scanner.h"

using namespace std;

int main(int argc, char** argv) {
    try
    {
        Scanner scan(argv[1]);
        Lex l;

        while ((l = scan.get_lex()).get_type() != LEX_FIN)
        {
            cout << l << endl;
        }
        return 0;
    }
    catch (char c)
    {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex l)
    {
        cout << "unexpected lex " << l << endl;
        return 1;
    }
    catch (...)
    {
        cout << "unexpected exception" << endl;
        return 1;
    }
}
