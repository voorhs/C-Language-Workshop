#include "vec_of_string.h"

VecOfString::VecOfString() : 
    size(0)
{
    content = new std::string[1];
    content[0] = "";
}

VecOfString::~VecOfString()
{
    delete[] content;
}

VecOfString::VecOfString(const std::initializer_list<std::string>& list)
{
    size = 0;
    content = new std::string[1];
    for (auto &elem : list)
		this->push_back(elem);
}

void VecOfString::push_back(std::string newElem)
{    
    std::string* newContent = new std::string[size + 1];

    for (int i = 0; i < size; ++i)
        newContent[i] = content[i];

    newContent[size++] = newElem;
    delete[] content;
    content = newContent;
}

int VecOfString::find(std::string key)
{
    for (int i = 0; i < size; ++i)
        if (content[i] == key)
            return i;
    return 0;
}

int VecOfString::get_size() const
{
    return size;
}

std::string VecOfString::operator[] (unsigned index)
{
    if (index < size)
        return content[index];
    return "";
}