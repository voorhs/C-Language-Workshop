#include "vec_of_ident.h"

VecOfIdent::VecOfIdent() : 
    size(0)
{
    content = new Ident[1];
    content[0] = Ident();
}

VecOfIdent::~VecOfIdent()
{
    delete[] content;
}

void VecOfIdent::push_back(Ident newElem)
{    
    Ident* newContent = new Ident[size + 1];

    for (int i = 0; i < size; ++i)
        newContent[i] = content[i];

    newContent[size++] = newElem;
    delete[] content;
    content = newContent;
}

int VecOfIdent::find(std::string name)
{
    for (int i = 0; i < size; ++i)
        if (content[i].get_name() == name)
            return i;
    return 0;
}

int VecOfIdent::get_size() const
{
    return size;
}

Ident& VecOfIdent::operator[] (unsigned index)
{
    return content[index];
}