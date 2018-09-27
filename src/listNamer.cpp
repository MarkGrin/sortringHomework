#include "listNamer.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>

ListNamer::ListNamer (const char* fileName)
{
    std::ifstream file;
    file.open (fileName, std::ios::in);
    if (!file)
    {
        throw std::runtime_error("Cant open file:" + std::string{fileName});
    }
    while (file)
    {
        std::string in;
        std::getline (file, in);
        if (in.size())
            names_.push_back (in);
    }
}

std::string ListNamer::getNextName () const
{

    if ( names_.size() )
        return names_.at(rand() % names_.size());
    return "unnamed";
}


