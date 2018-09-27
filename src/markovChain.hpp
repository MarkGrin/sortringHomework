#ifndef H_25CE5B5BF0BA4431ACAA45B94179C1D5

#define H_25CE5B5BF0BA4431ACAA45B94179C1D5

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>

template<int STEP>
class MarkovChain
{
    struct Block
    {
        char letters[STEP];
        std::map<std::string, std::size_t> links;
    };
    std::map<std::string, Block> block_;

    MarkovChain () = delete;

    void write (std::string& str, std::size_t i);
    void read (std::string& str, char letters[STEP+1]) const;

    public:

    MarkovChain (const char* fileName);

    std::string getNextName () const;

};

template <int STEP>
MarkovChain<STEP>::MarkovChain (const char* fileName)
{
    std::ifstream file;
    file.open (fileName, std::ios::in);
    if (!file)
    {
        std::cout << "File wasn't loaded:" << fileName << "\n";
        throw 0;
    }
    while (file)
    {
        std::string in;
        std::getline (file, in);
        for (std::size_t i = 0; i < in.size(); i++)
            if ( in.at(i) >= 'A' && in.at(i) <= 'Z' )
                in.at(i) += 'a' - 'A';
        write(in, 0);
    }
 
}

template <int STEP>
void MarkovChain<STEP>::write (std::string& str, std::size_t i)
{
    if ( str.size() < STEP + i + 1 )
        return ;
    char in[STEP+1];
    char to[STEP+1];
    for (std::size_t j = 0; j < STEP; j++)
        in[j] = str.at(i+j);
    for (std::size_t j = 0; j < STEP; j++)
        to[j] = str.at(i + j + 1);
    in[STEP] = 0;
    to[STEP] = 0;

    {
        auto it = block_.find(in);
        if ( it == block_.end() )
        {
            for (std::size_t j = 0; j < STEP; j++)
                block_[in].letters[j] = in[j];
        }
    }
    auto it = block_[in].links.find (to);
    if ( it == block_[in].links.end () )
    {
        block_[in].links[to] = 0;
    }
    block_[in].links[to] += 1;
    i++;
    write (str, i);
}

template <int STEP>
void MarkovChain<STEP>::read (std::string& str, char from[STEP+1]) const
{
    if ( str.size() > 4 + (rand()%6) )
    {
        return ;
    }

    {
        auto it = block_.find (from);
        if ( it == block_.end () )
        {
            for (std::size_t i = 0; i < STEP; i++)
            {
                str.push_back (from[i]);
            }
            return;
        }
    }
    auto fd = block_.find(from);
    auto& mapa = (*fd).second.links;
    std::size_t sum = 0;
    for (auto it = mapa.begin(); it != mapa.end(); it++)
    {
        sum += (*it).second;
    }
    std::size_t pick = rand() % sum;
    sum = 0;
    for (auto it = mapa.begin(); it != mapa.end(); it++)
    {
        if ( sum <= pick && sum + (*it).second > pick )
        {
            str.push_back (from[0]);
            for (std::size_t i = 0; i < STEP; i++)
                from[i] = (*it).first.at(i);
            read (str, from);
            return ;
        }
        sum += (*it).second;
    }
}

template <int STEP>
std::string MarkovChain<STEP>::getNextName () const
{
    std::size_t pick = rand() % block_.size();
    char from[STEP+1];
    from[STEP] = 0;
    auto it = block_.begin();
    for (std::size_t i = 0; i < pick; i++)
        it++;
    for (std::size_t i = 0; i < STEP; i++)
        from[i] = (*it).first.at(i);

    std::string result = "";
    read(result, from);

    result.at(0) -= 'a' - 'A';
    return result;
}

# endif /* H_25CE5B5BF0BA4431ACAA45B94179C1D5 */
