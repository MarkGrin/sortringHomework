#include "flat.hpp"
#include "sorts.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>


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
        auto get = [](std::string& str) {
            std::size_t comma = str.find(',');
            std::string result(str.begin(), str.begin() + comma);
            str.erase(0, comma + 1);
            return result;
        };
        Flat flat;
        flat.number = atoi(get(in).c_str());
        flat.roomsNumber = atoi(get(in).c_str());
        flat.ownerName = get(in) + " ";
        flat.ownerName.append (get(in) + " ");
        flat.ownerName.append (get(in));
        flat.occupantsNumber = atoi(in.c_str());
        flats.push_back(std::move(flat));
    }
    return flats;
}

namespace {
    namespace Statistics {
        std::size_t swaps = 0;
        std::size_t comparisons = 0;
    }
}

void swap (Flat& left, Flat& right) noexcept {
    Statistics::swaps++;
    Flat tmp (std::move(left));
    left = std::move(right);
    right = std::move(tmp);
}

template <typename Function>
void generateSort (std::string name, Function sorting) {
    std::ofstream file;
    file.open (name + "_result.csv", std::ios::out);

    for (std::size_t i = 1; i <= 20; i++) {
        auto flats = getFlats ("flats/flats" + std::to_string(i * 1000));

        Statistics::swaps = 0;
        Statistics::comparisons = 0;

        std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
        start_time = std::chrono::system_clock::now();

        sorting(flats.begin(), flats.end(), [](const Flat& a, const Flat& b) {
                Statistics::comparisons++;
                return a.ownerName < b.ownerName; });

        end_time = std::chrono::system_clock::now();
        std::size_t duration = std::chrono::duration_cast<std::chrono::microseconds>
                                                         (end_time - start_time).count();
         
        if ( !std::is_sorted(flats.begin(), flats.end(), [](const Flat& a, const Flat& b) {
                 return a.ownerName < b.ownerName;
                 }) )
                throw std::runtime_error("Bad sorting");

        file << flats.size() << "," << duration << "," << Statistics::comparisons << "," << Statistics::swaps << "\n";
        std::cout << name << ":" << flats.size() << " evaluated:" << duration << "\n";
    }
}

int main () {
    try {
        using compareFunction = bool (*)(const Flat&, const Flat&);
        generateSort("qsort", HWSorts::qsort<std::vector<Flat>::iterator, compareFunction>);
        generateSort("bubbleSort", HWSorts::bubbleSort<std::vector<Flat>::iterator, compareFunction>);
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
