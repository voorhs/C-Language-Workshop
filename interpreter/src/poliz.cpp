#include "poliz.h"

RPN::RPN() : 
    size(0)
{
    content = new RPN::lex[1];
    content[0] = RPN::lex();
}

void RPN::push_back(RPN::lex newElem)
{    
    RPN::lex* newContent = new RPN::lex[size + 1];

    for (int i = 0; i < size; ++i)
        newContent[i] = content[i];

    newContent[size++] = newElem;
    delete[] content;
    content = newContent;
}

int RPN::get_size() const
{
    return size;
}

RPN::lex& RPN::operator[] (unsigned index)
{
    return content[index];
}

std::ostream& operator<<(std::ostream& out, RPN& poliz)
{
    for (int i = 0; i < poliz.size; i++)
        out << i << ' ' << poliz.content[i] << std::endl;

    return out;
}
