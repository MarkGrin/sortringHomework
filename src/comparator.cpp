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
        Flat flat(std::move(in));
        flats.push_back(std::move(flat));
    }
    return flats;
}

void saveFlats (const std::string& name, const std::vector<Flat>& flats) {
    std::ofstream file;
    file.open (name, std::ios::out);
    if (!file)
    {
        throw std::runtime_error("Cant open file:" + std::string{name});
    }

    for (const auto& flat : flats) {
        std::string line = flat.serialize();
        file << line << "\n";
    }
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

    std::size_t sizes[] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};
    for (auto size : sizes) {
        auto flats = getFlats ("flats/flats" + std::to_string(size));

        Statistics::swaps = 0;
        Statistics::comparisons = 0;

        std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
        start_time = std::chrono::system_clock::now();

        sorting(flats.begin(), flats.end(), [](const Flat& a, const Flat& b) {
                Statistics::comparisons++;
                return a < b; });

        end_time = std::chrono::system_clock::now();
        std::size_t duration = std::chrono::duration_cast<std::chrono::microseconds>
                                                         (end_time - start_time).count();
         
        if ( !std::is_sorted(flats.begin(), flats.end()) )
                throw std::runtime_error("Bad sorting");
        
        saveFlats("sorted/" + name + std::to_string(size), flats);

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
