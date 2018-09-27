#include "flat.hpp"
#include "markovChain.hpp"
#include "listNamer.hpp"

#include <random>

/**
 * This program generates csv output of pseudo random Russian flats
 */
int main (int argc, char** argv) {

    if (argc < 5) {
        std::cout << "Need 4 parameters, text files with Russian names(FIO)"
                     " and number of flats generated\n";
        return 1;
    }


    ListNamer name(argv[2]);
    MarkovChain<4> surname(argv[1]);
    ListNamer patronymic(argv[3]);
    std::size_t size = atoi (argv[4]);

    for (std::size_t i = 1; i < size + 1; i++) {
        std::cout << i << ","
                  << (rand() % 3) + 1 << ","
                  << surname.getNextName() << ","
                  << name.getNextName() << ","
                  << patronymic.getNextName() << ","
                  << (rand() % 4) + 1 << "\n";
    }

    return 0;
}

