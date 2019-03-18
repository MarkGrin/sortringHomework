#include "hash_table.hpp"
#include "flat_h.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <map>

namespace {

    std::size_t random_index(std::size_t size) {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,size);
        return dist6(rng) % size;
    }
    std::vector<Flat> getFlats(const std::string &filename) {
        std::ifstream file;
        file.open(filename, std::ios::in);
        if (!file) {
            throw std::runtime_error("Cant open file:" + std::string{filename});
        }

        std::vector<Flat> flats;
        while (file) {
            std::string in;
            std::getline(file, in);
            if (in.empty())
                continue;
            Flat flat(std::move(in));
            flats.push_back(std::move(flat));
        }
        return flats;
    }

void generateSort(std::string name, std::function<std::size_t(const Flat&)> hash) {
    std::ofstream file;
    file.open(name + "_result.csv", std::ios::out);

    constexpr std::size_t elements = 5000;
    auto flats = getFlats("flats2/flats" + std::to_string(elements));
    for (std::size_t i = 1000; i < 1000*20; i += 1000) {
        hash_table<Flat> table(i, hash);
        for (const auto& flat : flats)
            table.add(flat);
        std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
        std::size_t time_summ = 0;
        for (std::size_t i = 0; i < 100; i++) {
            start_time = std::chrono::system_clock::now();
            table.find(flats.at(i));
            end_time = std::chrono::system_clock::now();
            std::size_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>
                (end_time - start_time).count();
            time_summ += duration;
        }
        if (i % 5000 == 0) {
            std::cout << "name:" << name << " coll:" << table.collisions() << "(" << (double(table.collisions()) / (elements)) << ")\n";
            std::cout << "size:" << double(i)/elements << "\n";
            std::cout << "time:" << time_summ << "\n";
        }
        file << table.collisions() << ","  << time_summ << "\n";
    }
    std::cout << "\n\n";
}

} // namespace

int main () {
    try {
        generateSort("slow", [](const Flat& flat) { return flat.slow_hash; });
        generateSort("fast", [](const Flat& flat) { return flat.fast_hash; });
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
