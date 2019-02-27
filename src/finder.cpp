#include "flat.hpp"
#include "sorts.hpp"
#include "find.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <map>

std::vector<Flat> getFlats(const std::string& filename) {
    std::ifstream file;
    file.open (filename, std::ios::in);
    if (!file)
    {
        throw std::runtime_error("Cant open file:" + std::string{filename});
    }

    std::vector<Flat> flats;
    while (file)
    {
        std::string in;
        std::getline (file, in);
        if (in.empty())
            continue;
        Flat flat(std::move(in));
        flats.push_back(std::move(flat));
    }
    return flats;
}

std::vector<Flat>::iterator straightSearch(std::vector<Flat>& flats, Flat flat) {
    return HWFind::straightSearch(flats.begin(), flats.end(), flat);
}

std::vector<Flat>::iterator binSearchNoSort(std::vector<Flat>& flats, Flat flat) {
    return HWFind::binarySearch(flats.begin(), flats.end(), flat);
}

std::vector<Flat>::iterator binSearchWithSort(std::vector<Flat>& flats, Flat flat) {
    HWSorts::qsort(flats.begin(), flats.end());
    return HWFind::binarySearch(flats.begin(), flats.end(), flat);
}

template <typename Function>
void generateSort (std::string name, Function search_func, bool do_sort, bool do_map) {
    std::ofstream file;
    file.open (name + "_result.csv", std::ios::out);

    std::vector<std::size_t> sizes = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000,
                                      50000, 100000, 200000, 500000, 1000000};

    for (auto size : sizes) {
        auto flats = getFlats ("flats/flats" + std::to_string(size));

        std::map<std::size_t, Flat> map;
        if (do_map)
            for (const auto& value : flats)
                map[value.number] = value;

        std::size_t sumDuration = 0;
        std::size_t tries = 10;
        for (std::size_t i = 0; i < tries; i++) {

            Flat flat = flats.at(i * (size/tries));

            if (!do_map) {
                if (do_sort)
                    std::sort(flats.begin(), flats.end());
            }

            std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
            start_time = std::chrono::system_clock::now();

            std::vector<Flat>::iterator it;


            if (do_map)
                map.find(flat.number);
            else
                it = search_func(flats, flat);


            end_time = std::chrono::system_clock::now();
            std::size_t duration = std::chrono::duration_cast<std::chrono::microseconds>
                    (end_time - start_time).count();


            if (!do_map && *it != flat) {
                throw std::runtime_error("Bad sorting");
            }
            sumDuration += duration;
        }
        sumDuration /= tries;

        file << name << "," << flats.size() << "," << sumDuration << "\n";
        std::cout << name << ":" << flats.size() << " evaluated:" << sumDuration << "\n";
    }
}

int main () {
    try {
        generateSort("bin_no_sort", binSearchNoSort, true, false);
        generateSort("bin_sort", binSearchWithSort, false, false);
        generateSort("straight", straightSearch, false, false);
        generateSort("map", straightSearch, false, true);
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
