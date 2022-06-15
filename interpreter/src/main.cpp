#include "lex.h"
#include "inter.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    Interpreter inter(argv[1]);
    return inter.perform(); 
}
