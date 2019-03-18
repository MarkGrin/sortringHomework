#include "flat.hpp"
#include "markovChain.hpp"
#include "listNamer.hpp"

#include <vector>
#include <random>
#include <cstdlib>

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

    std::size_t size = atoi(argv[4]);

    std::vector<Flat> flats;
    for (std::size_t i = 0; i < size; i++) {
        Flat flat;
        flat.number = i;
        flat.roomsNumber = rand() % 3 + 1;
        flat.ownerName;// = surname.getNextName() + "," + name.getNextName() + "," + patronymic.getNextName();
        for (std::size_t i = 0; i < 30; i++)
              flat.ownerName.push_back('a' + rand() % 20);
        flat.occupantsNumber = rand() % 3 + 1;
        flats.push_back(flat);
    }
    for (const auto& flat : flats) {
        std::cout << flat.serialize() << "\n";
    }

    return 0;
}

